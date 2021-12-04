mod traits;
use traits::NewsArticle;
use traits::Tweet;

use traits::returns_summarizable;
use traits::Summary;

fn main() {
    let tweet = Tweet {
        username: "horse_ebooks".to_string(),
        content: "of course, as you already know, people".to_string(),
        reply: false,
        retweet: false,
    };

    println!("1 new tweet: {}", tweet.summarize());

    let article = NewsArticle {
        headline: String::from("Penguins win the Stanley Cup Championship!"),
        location: String::from("Pittsburgh, PA, USA"),
        author: String::from("Iceburgh"),
        content: String::from(
            "The Pittsburgh Penguins once again are the best \
             hockey team in the NHL.",
        ),
    };

    let second_tweet = returns_summarizable();
    println!("New tweet available! {}", second_tweet.summarize());

    println!("New article available! {}", article.summarize());
}
