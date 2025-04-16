# Tmux Cheat Sheet

## Basic Commands

| Command | Description |
|---------|-------------|
| `tmux` | Start a new tmux session |
| `tmux new -s name` | Start a new session with name |
| `tmux attach` or `tmux a` | Attach to the last session |
| `tmux attach -t name` | Attach to a session named "name" |
| `tmux ls` | List all sessions |
| `tmux kill-session -t name` | Kill session "name" |
| `tmux kill-server` | Kill all sessions |
| `exit` or `Ctrl+d` | Exit current tmux pane |

## Prefix Key

In your configuration, the prefix key is set to **Ctrl+Space**. All the following commands require pressing the prefix key first, then the command key.

## Session Management

| Command | Description |
|---------|-------------|
| `d` | Detach from current session |
| `s` | Show session list |
| `$` | Rename current session |
| `)` | Switch to next session |
| `(` | Switch to previous session |

## Window Management

| Command | Description |
|---------|-------------|
| `c` | Create a new window |
| `,` | Rename current window |
| `w` | List all windows |
| `n` | Move to next window |
| `p` | Move to previous window |
| `0-9` | Switch to window number 0-9 |
| `f` | Find window by name |
| `&` | Kill current window |
| `.` | Move window to a different number |

## Pane Management

| Command | Description |
|---------|-------------|
| `%` | Split pane horizontally |
| `"` | Split pane vertically |
| `h`, `j`, `k`, `l` | Navigate between panes (set in your config) |
| `o` | Go to next pane |
| `q` | Show pane numbers |
| `q 0-9` | Switch to pane number |
| `z` | Toggle pane zoom |
| `}` | Swap with next pane |
| `{` | Swap with previous pane |
| `x` | Kill current pane |
| `!` | Convert pane into a window |
| `Ctrl+Arrow` | Resize pane in direction of arrow |
| `Alt+Arrow` | Resize pane in 5-cell increments |

## Copy Mode (Vi Mode)

| Command | Description |
|---------|-------------|
| `[` | Enter copy mode |
| `q` | Quit copy mode |
| `Space` | Start selection |
| `Enter` | Copy selection |
| `Esc` | Clear selection |
| `/` | Search forward |
| `?` | Search backward |
| `n` | Next search match |
| `N` | Previous search match |
| `g` | Go to top |
| `G` | Go to bottom |
| `h`, `j`, `k`, `l` | Vi navigation |

## Other Useful Commands

| Command | Description |
|---------|-------------|
| `r` | Reload tmux config (set in your config) |
| `t` | Show a clock |
| `:` | Enter tmux command prompt |
| `?` | Show key bindings |

## Mouse Support

Your configuration has mouse mode enabled, so you can:
- Click on a pane to select it
- Drag pane borders to resize
- Scroll with the mouse wheel 
- Click on a window name to select it
- Drag and drop windows in the status bar

## TPM (Tmux Plugin Manager) Commands

| Command | Description |
|---------|-------------|
| `I` | Install new plugins |
| `U` | Update plugins |
| `Alt+u` | Remove/uninstall plugins not in list |# Tmux Cheat Sheet

## Basic Commands

| Command | Description |
|---------|-------------|
| `tmux` | Start a new tmux session |
| `tmux new -s name` | Start a new session with name |
| `tmux attach` or `tmux a` | Attach to the last session |
| `tmux attach -t name` | Attach to a session named "name" |
| `tmux ls` | List all sessions |
| `tmux kill-session -t name` | Kill session "name" |
| `tmux kill-server` | Kill all sessions |
| `exit` or `Ctrl+d` | Exit current tmux pane |

## Prefix Key

In your configuration, the prefix key is set to **Ctrl+Space**. All the following commands require pressing the prefix key first, then the command key.

## Session Management

| Command | Description |
|---------|-------------|
| `d` | Detach from current session |
| `s` | Show session list |
| `$` | Rename current session |
| `)` | Switch to next session |
| `(` | Switch to previous session |

## Window Management

| Command | Description |
|---------|-------------|
| `c` | Create a new window |
| `,` | Rename current window |
| `w` | List all windows |
| `n` | Move to next window |
| `p` | Move to previous window |
| `0-9` | Switch to window number 0-9 |
| `f` | Find window by name |
| `&` | Kill current window |
| `.` | Move window to a different number |

## Pane Management

| Command | Description |
|---------|-------------|
| `%` | Split pane horizontally |
| `"` | Split pane vertically |
| `h`, `j`, `k`, `l` | Navigate between panes (set in your config) |
| `o` | Go to next pane |
| `q` | Show pane numbers |
| `q 0-9` | Switch to pane number |
| `z` | Toggle pane zoom |
| `}` | Swap with next pane |
| `{` | Swap with previous pane |
| `x` | Kill current pane |
| `!` | Convert pane into a window |
| `Ctrl+Arrow` | Resize pane in direction of arrow |
| `Alt+Arrow` | Resize pane in 5-cell increments |

## Copy Mode (Vi Mode)

| Command | Description |
|---------|-------------|
| `[` | Enter copy mode |
| `q` | Quit copy mode |
| `Space` | Start selection |
| `Enter` | Copy selection |
| `Esc` | Clear selection |
| `/` | Search forward |
| `?` | Search backward |
| `n` | Next search match |
| `N` | Previous search match |
| `g` | Go to top |
| `G` | Go to bottom |
| `h`, `j`, `k`, `l` | Vi navigation |

## Other Useful Commands

| Command | Description |
|---------|-------------|
| `r` | Reload tmux config (set in your config) |
| `t` | Show a clock |
| `:` | Enter tmux command prompt |
| `?` | Show key bindings |

## Mouse Support

Your configuration has mouse mode enabled, so you can:
- Click on a pane to select it
- Drag pane borders to resize
- Scroll with the mouse wheel 
- Click on a window name to select it
- Drag and drop windows in the status bar

## TPM (Tmux Plugin Manager) Commands

| Command | Description |
|---------|-------------|
| `I` | Install new plugins |
| `U` | Update plugins |
| `Alt+u` | Remove/uninstall plugins not in list |
