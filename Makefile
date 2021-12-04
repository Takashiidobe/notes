SOURCE_DOCS := $(shell find src -type f -name "*.md")

HTML_FILES=$(SOURCE_DOCS:src/%.md=site/%.html)

all: $(HTML_FILES) ./build_index.js
	miniserve site

html: $(HTML_FILES) ./build_index.js

site/%.html: src/%.md templates/site.html
	pandoc -f markdown+fenced_divs -s $< -o $@ --table-of-contents --template templates/site.html

clean:
	rm -r site/*

# .PHONY: mkdirs
# mkdirs:
# 	find src -type d -print0 >dirs.txt
# 	xargs -0 mkdir -p <dirs.txt
# 	rm dirs.txt
