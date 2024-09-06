#define pressed(b) (input->buttons[b].is_down && input->buttons[b].is_changed)
#define down(b) input->buttons[b].is_down
#define released(b) (!input->buttons[b].is_down && input->buttons[b].is_changed)

static void simulate_game(struct Input* input) {
    clear_screen(0xff5500);

    if (input->buttons[BUTTON_UP].is_down)
        draw_rect(0.0, 0.0, 20.0, 5.0, 0x00ff18);
}