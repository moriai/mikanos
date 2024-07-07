Rectangle<int> Terminal::InputKey(
    uint8_t modifier, uint8_t keycode, char ascii) {
  DrawCursor(false);

  Rectangle<int> draw_area{CalcCursorPos(), {8*2, 16}};

  if (ascii == '\n') {
    linebuf_[linebuf_index_] = 0;
    linebuf_index_ = 0;
    cursor_.x = 0;
    if (cursor_.y < kRows - 1) {
      ++cursor_.y;
    } else {
      Scroll1();
    }
    ExecuteLine();
    Print(">");
    draw_area.pos = ToplevelWindow::kTopLeftMargin;
    draw_area.size = window_->InnerSize();
  }

  DrawCursor(true);

  return draw_area;
}

void Terminal::ExecuteLine() {
  char* command = &linebuf_[0];
  char* first_arg = strchr(&linebuf_[0], ' ');
  if (first_arg) {
    *first_arg = 0;
    ++first_arg;
  }

  if (strcmp(command, "echo") == 0) {
    if (first_arg) {
      Print(first_arg);
    }
    Print("\n");
  } else if (command[0] != 0) {
    Print("no such command: ");
    Print(command);
    Print("\n");
  }
}
