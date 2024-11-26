---
title: Newsboat
date created: Thursday, November 30th 2023, 7:35:53 pm
date modified: Tuesday, November 26th 2024, 8:32:00 am
---

# Newsboat

## URLs

You can set the urls you want it to parse in `$HOME/.newsboat/urls`

Newsboat is an RSS reader. I set it up to have vim keybinds using this config file (in $HOME/.newsboat/config)

## Config

```sh
# -- feeds ---------------------------------------------------------------------

auto-reload yes
reload-time 120
reload-threads 4
download-retries 4
download-timeout 10
prepopulate-query-feeds yes


# -- display -------------------------------------------------------------------

show-read-feeds no
feed-sort-order unreadarticlecount-asc

color info default default reverse
color listnormal_unread yellow default
color listfocus blue default reverse bold
color listfocus_unread blue default reverse bold

text-width 80


# -- navigation ----------------------------------------------------------------

goto-next-feed no

browser "open %u"

bind-key j down feedlist
bind-key k up feedlist
bind-key j next articlelist
bind-key k prev articlelist
bind-key J nex-feed articlelist
bind-key K prev-feed articlelist
bind-key j down article
bind-key k up article


# -- bookmarks -----------------------------------------------------------------

bookmark-cmd ~/.newsbeuter/bookmark.sh
bookmark-interactive no
bookmark-autopilot yes


# -- misc ----------------------------------------------------------------------

unbind-key C feedlist
confirm-exit no
cleanup-on-quit no
pager bat
```
