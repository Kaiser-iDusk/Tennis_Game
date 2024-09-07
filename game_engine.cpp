#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].is_changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].is_changed)

global_variable float player_pos_x = 0.f, player_pos_y = 0.f; // depreceatd speed = 150.f;
global_variable float player_v_y = 0.f;

global_variable float ai_pos_x = 0.f, ai_pos_y = 0.f;
global_variable float ai_v_y = 0.f;

static void simulate_game(struct Input* input, float dt) {
    clear_screen(0xdecea9);

    // init
    player_pos_x = 0.9 * (render_state.w / 2.f);
    ai_pos_x = -0.9 * (render_state.w / 2.f);

    // borders and props
    float border_thickness = 6.f;

    draw_rect(0.f, (render_state.h / 2.f), (render_state.w / 2.f), border_thickness, 0xff0000);
    draw_rect(0.f, -(render_state.h / 2.f), (render_state.w / 2.f), border_thickness, 0xff0000);
    draw_rect((render_state.w / 2.f), 0.f, border_thickness, (render_state.h / 2.f), 0xff0000);
    draw_rect(-(render_state.w / 2.f), 0.f, border_thickness, (render_state.h / 2.f), 0xff0000);

        // game-net
    draw_rect(0.f, 0.f, 4.f, (render_state.h / 2.f), 0xffffff);

    // physics
    float player_acc_y = 0.f, ai_acc_y = 0.f;

    if (is_down(BUTTON_UP)) player_acc_y += 500.f;
    if (is_down(BUTTON_DOWN)) player_acc_y -= 500.f;

    if (is_down(BUTTON_W)) ai_acc_y += 500.f;
    if (is_down(BUTTON_S)) ai_acc_y -= 500.f;
        // if (is_down(BUTTON_LEFT)) player_pos_x -= (speed * dt);
        // if (is_down(BUTTON_RIGHT)) player_pos_x += (speed * dt);

    // friction
    player_acc_y -= (player_v_y * 1.11f);
    ai_acc_y -= (ai_v_y * 1.11f);

    // motion equations
    player_pos_y += ((player_v_y * dt) + (player_acc_y * dt * dt * 0.5));
    player_v_y += (player_acc_y * dt);

    ai_pos_y += ((ai_v_y * dt) + (ai_acc_y * dt * dt * 0.5));
    ai_v_y += (ai_acc_y * dt);
    
    // collision mechanics
    if (player_pos_y + 75.f > (render_state.h / 2.f) - border_thickness) {
        player_pos_y = (render_state.h / 2.f) - border_thickness - 75.f;
        player_v_y *= -.33f;
    }
    else if (player_pos_y - 75.f < -(render_state.h / 2.f) + border_thickness) {
        player_pos_y = -(render_state.h / 2.f) + border_thickness + 75.f;
        player_v_y *= -.33f;
    }

    if (ai_pos_y + 75.f > (render_state.h / 2.f) - border_thickness) {
        ai_pos_y = (render_state.h / 2.f) - border_thickness - 75.f;
        ai_v_y *= -.33f;
    }
    else if (ai_pos_y - 75.f < -(render_state.h / 2.f) + border_thickness) {
        ai_pos_y = -(render_state.h / 2.f) + border_thickness + 75.f;
        ai_v_y *= -.33f;
    }

    // render updated states
    draw_rect(player_pos_x, player_pos_y, 15.0, 75.0, 0x00db02);
    draw_rect(ai_pos_x, ai_pos_y, 15.0, 75.0, 0xff00ff);
}