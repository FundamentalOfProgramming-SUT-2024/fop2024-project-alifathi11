#include <termbox.h>

int main() {
    tb_init();
    tb_change_cell(10, 10, '▒', TB_WHITE, TB_BLACK);
    tb_present();
    tb_wait();
    tb_shutdown();
    return 0;
}
