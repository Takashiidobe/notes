import re

from recipe_scrapers import scrape_html


def scrape_recipe(url):
    scraper = scrape_html(html=None, org_url=url, supported_only=False, online=True)
    s = ""
    snake_cased_title = (
        scraper.title()
        .replace(" ", "-")
        .replace("(", "")
        .replace(")", "")
        .replace("&", "and")
        .lower()
    )
    snake_cased_title = re.sub("[^a-zA-Z-]", "", snake_cased_title)
    snake_cased_title = snake_cased_title + ".md"

    if scraper.image() and scraper.title():
        s += "---\n"
        s += f"title: {scraper.title()}\n"
        s += "---\n"
        s += "\n"
        s += f"![{scraper.title()}]({scraper.image()})\n\n"
    if scraper.title():
        s += f"# {scraper.title()}\n\n"
    if scraper.url:
        s += f"- From: [link]({scraper.url})\n\n"
    try:
        if scraper.cook_time() or scraper.total_time():
            times_to_cook = filter([scraper.cook_time(), scraper.total_time()])
            cook_time = list(times_to_cook)[0]
            s += f"- Cooking Time: {cook_time} minutes\n\n"
    except:
        pass
    if scraper.ingredients():
        s += "## Ingredients:\n\n"
        for i in scraper.ingredients():
            s += f"- {i}\n"
        s += "\n"
    if scraper.instructions():
        s += "## Instructions:\n\n"
        s += scraper.instructions().replace("\n", "\n\n") + "\n"

    with open(f"recipes/{snake_cased_title}", "w+") as f:
        f.write(s)

    return (
        snake_cased_title,
        scraper.title().replace("(", "").replace(")", "").replace("&", "and"),
    )


recipes = []

with open("recipes_to_scrape.txt", "r") as f:
    for line in f:
        if line:
            recipes.append(scrape_recipe(line.strip()))

with open("./recipes/_recipes.md", "a") as f:
    for (file_name, title) in recipes:
        f.write(f"- [{title.title()}](./{file_name[:-3]})\n")
