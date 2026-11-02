#include QMK_KEYBOARD_H
#include "oled_tetris.h"

#ifdef OLED_ENABLE

#define OLED_TETRIS_WIDTH          5
#define OLED_TETRIS_HEIGHT         16
#define OLED_TETRIS_BOARD_MASK     ((1U << OLED_TETRIS_WIDTH) - 1U)
#define OLED_TETRIS_FRAME_DURATION 250
#define OLED_TETRIS_PIECE_COUNT    5
#define OLED_TETRIS_MAX_ROTATIONS  4

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t rows[4];
} oled_tetris_shape_t;

typedef struct {
    uint8_t             rotation_count;
    oled_tetris_shape_t rotations[OLED_TETRIS_MAX_ROTATIONS];
} oled_tetris_piece_t;

static const oled_tetris_piece_t oled_tetris_pieces[OLED_TETRIS_PIECE_COUNT] = {
    {2, {
            {4, 1, {0x0F, 0x00, 0x00, 0x00}},
            {1, 4, {0x01, 0x01, 0x01, 0x01}},
            {0, 0, {0x00, 0x00, 0x00, 0x00}},
            {0, 0, {0x00, 0x00, 0x00, 0x00}},
        }},
    {1, {
            {2, 2, {0x03, 0x03, 0x00, 0x00}},
            {0, 0, {0x00, 0x00, 0x00, 0x00}},
            {0, 0, {0x00, 0x00, 0x00, 0x00}},
            {0, 0, {0x00, 0x00, 0x00, 0x00}},
        }},
    {4, {
            {3, 2, {0x07, 0x02, 0x00, 0x00}},
            {2, 3, {0x01, 0x03, 0x01, 0x00}},
            {3, 2, {0x02, 0x07, 0x00, 0x00}},
            {2, 3, {0x02, 0x03, 0x02, 0x00}},
        }},
    {4, {
            {2, 3, {0x01, 0x01, 0x03, 0x00}},
            {3, 2, {0x07, 0x04, 0x00, 0x00}},
            {2, 3, {0x03, 0x02, 0x02, 0x00}},
            {3, 2, {0x01, 0x07, 0x00, 0x00}},
        }},
    {2, {
            {3, 2, {0x06, 0x03, 0x00, 0x00}},
            {2, 3, {0x01, 0x03, 0x02, 0x00}},
            {0, 0, {0x00, 0x00, 0x00, 0x00}},
            {0, 0, {0x00, 0x00, 0x00, 0x00}},
        }},
};

static uint8_t  oled_tetris_board[OLED_TETRIS_HEIGHT] = {0};
static uint8_t  oled_tetris_piece_id                   = 0;
static uint8_t  oled_tetris_piece_cycle                = 0;
static uint8_t  oled_tetris_spawn_cycle                = 0;
static uint8_t  oled_tetris_piece_rotation             = 0;
static uint8_t  oled_tetris_target_rotation            = 0;
static int8_t   oled_tetris_piece_x                    = 0;
static int8_t   oled_tetris_piece_y                    = 0;
static int8_t   oled_tetris_target_x                   = 0;
static uint32_t oled_tetris_timer                      = 0;
static bool     oled_tetris_started                    = false;

static const oled_tetris_shape_t *tetris_get_shape(uint8_t piece_id, uint8_t rotation) {
    const oled_tetris_piece_t *piece = &oled_tetris_pieces[piece_id];
    return &piece->rotations[rotation % piece->rotation_count];
}

static bool tetris_piece_collides(uint8_t piece_id, uint8_t rotation, int8_t x, int8_t y) {
    const oled_tetris_shape_t *shape = tetris_get_shape(piece_id, rotation);

    if (x < 0 || (uint8_t)(x + shape->width) > OLED_TETRIS_WIDTH) {
        return true;
    }

    for (uint8_t row = 0; row < shape->height; row++) {
        uint8_t mask      = shape->rows[row] << x;
        int8_t  board_row = y + row;

        if (board_row >= OLED_TETRIS_HEIGHT) {
            return true;
        }

        if ((oled_tetris_board[board_row] & mask) != 0) {
            return true;
        }
    }

    return false;
}

static void tetris_reset_board(void) {
    for (uint8_t row = 0; row < OLED_TETRIS_HEIGHT; row++) {
        oled_tetris_board[row] = 0;
    }
}

static int8_t tetris_find_landing_y(uint8_t piece_id, uint8_t rotation, int8_t x) {
    int8_t y = 0;

    if (tetris_piece_collides(piece_id, rotation, x, y)) {
        return -1;
    }

    while (!tetris_piece_collides(piece_id, rotation, x, y + 1)) {
        y++;
    }

    return y;
}

static void tetris_copy_board(uint8_t *destination) {
    for (uint8_t row = 0; row < OLED_TETRIS_HEIGHT; row++) {
        destination[row] = oled_tetris_board[row];
    }
}

static void tetris_place_piece_on_board(uint8_t *board, uint8_t piece_id, uint8_t rotation, int8_t x, int8_t y) {
    const oled_tetris_shape_t *shape = tetris_get_shape(piece_id, rotation);

    for (uint8_t row = 0; row < shape->height; row++) {
        board[y + row] |= shape->rows[row] << x;
    }
}

static uint8_t tetris_count_completed_lines(const uint8_t *board) {
    uint8_t lines = 0;

    for (uint8_t row = 0; row < OLED_TETRIS_HEIGHT; row++) {
        if ((board[row] & OLED_TETRIS_BOARD_MASK) == OLED_TETRIS_BOARD_MASK) {
            lines++;
        }
    }

    return lines;
}

static uint8_t tetris_column_height(const uint8_t *board, uint8_t col) {
    for (uint8_t row = 0; row < OLED_TETRIS_HEIGHT; row++) {
        if ((board[row] & (1U << col)) != 0) {
            return OLED_TETRIS_HEIGHT - row;
        }
    }

    return 0;
}

static uint8_t tetris_count_holes(const uint8_t *board) {
    uint8_t holes = 0;

    for (uint8_t col = 0; col < OLED_TETRIS_WIDTH; col++) {
        bool block_seen = false;

        for (uint8_t row = 0; row < OLED_TETRIS_HEIGHT; row++) {
            bool filled = (board[row] & (1U << col)) != 0;

            if (filled) {
                block_seen = true;
            } else if (block_seen) {
                holes++;
            }
        }
    }

    return holes;
}

static uint8_t tetris_abs_diff(int8_t a, int8_t b) {
    return (a > b) ? (uint8_t)(a - b) : (uint8_t)(b - a);
}

static int16_t tetris_score_position(uint8_t piece_id, uint8_t rotation, int8_t x) {
    uint8_t temp_board[OLED_TETRIS_HEIGHT];
    uint8_t lines;
    uint8_t holes;
    uint8_t previous_height = 0;
    uint8_t aggregate_height = 0;
    uint8_t bumpiness = 0;
    int8_t  landing_y = tetris_find_landing_y(piece_id, rotation, x);

    if (landing_y < 0) {
        return INT16_MIN;
    }

    tetris_copy_board(temp_board);
    tetris_place_piece_on_board(temp_board, piece_id, rotation, x, landing_y);

    lines = tetris_count_completed_lines(temp_board);
    holes = tetris_count_holes(temp_board);

    for (uint8_t col = 0; col < OLED_TETRIS_WIDTH; col++) {
        uint8_t height = tetris_column_height(temp_board, col);

        aggregate_height += height;

        if (col > 0) {
            bumpiness += tetris_abs_diff((int8_t)height, (int8_t)previous_height);
        }

        previous_height = height;
    }

    return (int16_t)(lines * 120) - (int16_t)(holes * 24) - (int16_t)(aggregate_height * 5) - (int16_t)(bumpiness * 4);
}

static void tetris_choose_target(uint8_t piece_id) {
    int8_t  best_x     = 0;
    int16_t best_score = INT16_MIN;

    oled_tetris_target_rotation = 0;
    oled_tetris_target_x        = 0;

    for (uint8_t rotation = 0; rotation < oled_tetris_pieces[piece_id].rotation_count; rotation++) {
        const oled_tetris_shape_t *shape       = tetris_get_shape(piece_id, rotation);
        int8_t                     preferred_x = (oled_tetris_spawn_cycle % 2 == 0) ? 0 : (OLED_TETRIS_WIDTH - shape->width);

        for (int8_t x = 0; x <= (int8_t)(OLED_TETRIS_WIDTH - shape->width); x++) {
            int16_t score = tetris_score_position(piece_id, rotation, x);

            if (score > best_score || (score == best_score && tetris_abs_diff(x, preferred_x) < tetris_abs_diff(best_x, preferred_x))) {
                best_score                = score;
                best_x                    = x;
                oled_tetris_target_rotation = rotation;
                oled_tetris_target_x        = x;
            }
        }
    }
}

static void tetris_spawn_piece(void) {
    const oled_tetris_piece_t *piece = &oled_tetris_pieces[oled_tetris_piece_id];
    const oled_tetris_shape_t *shape;

    oled_tetris_piece_id = oled_tetris_piece_cycle;
    oled_tetris_piece_cycle = (oled_tetris_piece_cycle + 1) % OLED_TETRIS_PIECE_COUNT;
    piece = &oled_tetris_pieces[oled_tetris_piece_id];

    tetris_choose_target(oled_tetris_piece_id);

    if (piece->rotation_count > 1) {
        oled_tetris_piece_rotation = (oled_tetris_target_rotation + 1 + (oled_tetris_spawn_cycle % (piece->rotation_count - 1))) % piece->rotation_count;
    } else {
        oled_tetris_piece_rotation = 0;
    }

    shape = tetris_get_shape(oled_tetris_piece_id, oled_tetris_piece_rotation);
    oled_tetris_piece_x = (OLED_TETRIS_WIDTH - shape->width) / 2;
    oled_tetris_piece_y = 0;

    if (tetris_piece_collides(oled_tetris_piece_id, oled_tetris_piece_rotation, oled_tetris_piece_x, oled_tetris_piece_y)) {
        tetris_reset_board();
        shape = tetris_get_shape(oled_tetris_piece_id, oled_tetris_piece_rotation);
        oled_tetris_piece_x = (OLED_TETRIS_WIDTH - shape->width) / 2;
        oled_tetris_piece_y = 0;
    }

    oled_tetris_spawn_cycle++;
}

static void tetris_clear_lines(void) {
    for (int8_t row = OLED_TETRIS_HEIGHT - 1; row >= 0; row--) {
        if ((oled_tetris_board[row] & OLED_TETRIS_BOARD_MASK) == OLED_TETRIS_BOARD_MASK) {
            for (int8_t shift = row; shift > 0; shift--) {
                oled_tetris_board[shift] = oled_tetris_board[shift - 1];
            }
            oled_tetris_board[0] = 0;
            row++;
        }
    }
}

static void tetris_lock_piece(void) {
    const oled_tetris_shape_t *shape = tetris_get_shape(oled_tetris_piece_id, oled_tetris_piece_rotation);

    for (uint8_t row = 0; row < shape->height; row++) {
        oled_tetris_board[oled_tetris_piece_y + row] |= shape->rows[row] << oled_tetris_piece_x;
    }

    tetris_clear_lines();
    tetris_spawn_piece();
}

static uint8_t tetris_next_rotation(void) {
    uint8_t count          = oled_tetris_pieces[oled_tetris_piece_id].rotation_count;
    uint8_t forward_steps  = (oled_tetris_target_rotation + count - oled_tetris_piece_rotation) % count;
    uint8_t backward_steps = (oled_tetris_piece_rotation + count - oled_tetris_target_rotation) % count;

    if (forward_steps <= backward_steps) {
        return (oled_tetris_piece_rotation + 1) % count;
    }

    return (oled_tetris_piece_rotation + count - 1) % count;
}

static void tetris_rotate_toward_target(void) {
    static const int8_t kicks[] = {0, 1, -1};

    if (oled_tetris_piece_rotation == oled_tetris_target_rotation) {
        return;
    }

    uint8_t next_rotation = tetris_next_rotation();

    for (uint8_t i = 0; i < ARRAY_SIZE(kicks); i++) {
        int8_t candidate_x = oled_tetris_piece_x + kicks[i];

        if (!tetris_piece_collides(oled_tetris_piece_id, next_rotation, candidate_x, oled_tetris_piece_y)) {
            oled_tetris_piece_rotation = next_rotation;
            oled_tetris_piece_x        = candidate_x;
            return;
        }
    }
}

static void tetris_advance(void) {
    if (!oled_tetris_started) {
        tetris_reset_board();
        oled_tetris_piece_cycle = 0;
        oled_tetris_spawn_cycle = 0;
        tetris_spawn_piece();
        oled_tetris_timer   = timer_read32();
        oled_tetris_started = true;
    }

    if (timer_elapsed32(oled_tetris_timer) > OLED_TETRIS_FRAME_DURATION) {
        oled_tetris_timer = timer_read32();

        tetris_rotate_toward_target();

        if (oled_tetris_piece_x < oled_tetris_target_x && !tetris_piece_collides(oled_tetris_piece_id, oled_tetris_piece_rotation, oled_tetris_piece_x + 1, oled_tetris_piece_y)) {
            oled_tetris_piece_x++;
        } else if (oled_tetris_piece_x > oled_tetris_target_x && !tetris_piece_collides(oled_tetris_piece_id, oled_tetris_piece_rotation, oled_tetris_piece_x - 1, oled_tetris_piece_y)) {
            oled_tetris_piece_x--;
        }

        if (tetris_piece_collides(oled_tetris_piece_id, oled_tetris_piece_rotation, oled_tetris_piece_x, oled_tetris_piece_y + 1)) {
            tetris_lock_piece();
        } else {
            oled_tetris_piece_y++;
        }
    }
}

void oled_tetris_render(void) {
    const oled_tetris_shape_t *shape;
    char                       row_text[6];

    tetris_advance();
    shape = tetris_get_shape(oled_tetris_piece_id, oled_tetris_piece_rotation);

    for (uint8_t row = 0; row < OLED_TETRIS_HEIGHT; row++) {
        uint8_t mask = oled_tetris_board[row];

        if (row >= (uint8_t)oled_tetris_piece_y && row < (uint8_t)(oled_tetris_piece_y + shape->height)) {
            mask |= shape->rows[row - oled_tetris_piece_y] << oled_tetris_piece_x;
        }

        for (uint8_t col = 0; col < OLED_TETRIS_WIDTH; col++) {
            row_text[col] = (mask & (1U << col)) ? '#' : ' ';
        }
        row_text[OLED_TETRIS_WIDTH] = '\0';

        oled_set_cursor(0, row);
        oled_write(row_text, false);
    }
}

#endif
