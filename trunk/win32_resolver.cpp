#include "win32_resolver.h"
#include <iostream>

set_parent_fn
Win_Resolver::resolve_set_parent()
{
    set_parent_fn set_parent = (set_parent_fn) user32->resolve("SetParent");
    if (set_parent)
        return set_parent;
    else
        {
        std::cout << "WIN32 RESOLVER - Set Parent failed!" << std::endl;
        return 0;
        }
}

get_window_rect_fn
Win_Resolver::resolve_get_window_rect()
{
    get_window_rect_fn gwr = (get_window_rect_fn) user32->resolve("GetWindowRect");
    if (gwr)
        return gwr;
    else
        {
        std::cout << "WIN32 RESOLVER - Get Window Rect failed!" << std::endl;
        return 0;
        }
}

get_client_rect_fn
Win_Resolver::resolve_get_client_rect()
{
    get_client_rect_fn gcr = (get_client_rect_fn) user32->resolve("GetClientRect");
    if (gcr)
        return gcr;
    else
        {
        std::cout << "WIN32 RESOLVER - Get Client Rect failed!" << std::endl;
        return 0;
        }
}


move_window_fn
Win_Resolver::resolve_move_window()
{
    move_window_fn mw = (move_window_fn) user32->resolve("MoveWindow");
    if (mw)
        return mw;
    else
        {
        std::cout << "WIN32 RESOLVER - Move Win failed!" << std::endl;
        return 0;
        }
}

Win_Resolver::Win_Resolver()
{
    this->user32 = new QLibrary("user32.dll");
}

Win_Resolver::~Win_Resolver()
{
    delete this->user32;
}

