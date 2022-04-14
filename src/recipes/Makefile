all:
	make scrape && make move_recipes
scrape:
	python3 scrape.py
move_recipes:
	echo "" >> recipes.txt && \
	cat recipes_to_scrape.txt >> recipes.txt && \
	rm recipes_to_scrape.txt && \
	touch recipes_to_scrape.txt
