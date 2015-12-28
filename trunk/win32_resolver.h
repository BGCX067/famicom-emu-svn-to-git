#ifndef WIN_RESOLVER_HDR
#define WIN_RESOLVER_HDR

#include <QLibrary>
#include "SDL_syswm.h"


typedef HWND (APIENTRY *set_parent_fn) (HWND, HWND);
typedef BOOL (APIENTRY *get_window_rect_fn) (HWND, LPRECT);
typedef BOOL (APIENTRY *get_client_rect_fn) (HWND, LPRECT);
typedef BOOL (APIENTRY *move_window_fn) (HWND, int, int, int, int, BOOL);

class Win_Resolver
{
public:
    Win_Resolver();
    ~Win_Resolver();
    set_parent_fn   resolve_set_parent();
    get_window_rect_fn  resolve_get_window_rect();
    get_client_rect_fn  resolve_get_client_rect();
    move_window_fn      resolve_move_window();

private:
    QLibrary*    user32;
};

#endif
