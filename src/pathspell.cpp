#include <ncurses.h>

class N_Window
{
public:
  N_Window();
  virtual ~N_Window();
};

N_Window::N_Window()
{
  initscr();
}

N_Window::~N_Window()
{
  endwin();
}

int main()
{
  N_Window window;
}
