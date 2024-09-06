#define down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].is_changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].is_changed)

global_variable float player_pos_x = 0.f, player_pos_y = 0.f;

static void simulate_game(struct Input* input) {
    clear_screen(0xffff05);

    if (pressed(BUTTON_UP)) player_pos_y -= .1f;
    if (pressed(BUTTON_DOWN)) player_pos_y += .1f;
    if (pressed(BUTTON_LEFT)) player_pos_x -= .1f;
    if (pressed(BUTTON_RIGHT)) player_pos_x += .1f;
    
    draw_rect(player_pos_x, player_pos_y, 5.0, 100.0, 0xff5500);
}