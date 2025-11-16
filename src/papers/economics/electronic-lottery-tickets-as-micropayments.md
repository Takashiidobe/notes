---
title: "Electronic Lottery Tickets As Micropayments"
pdf_url: "[[electronic-lottery-tickets-as-micropayments.pdf]]"
---
## Notes

This paper discusses handling micropayments as probabilistic payments with electronic lottery tickets. For example, a $1 prize that's given out equally to 100 people would have an expected value of 1 cent, however, the vendor would only have to handle the transaction cost of handing out 1 payment, but they still have to accept 1 cent payments, so they would receive 100 payments + give out 1 payment vs. receiving 100 payments + giving out 100 payments. For very small and frequent transactions, this does have its merits.

I had many questions reading this paper on its practicality. The probabilistic payment idea is well accepted (Algorand uses distributed proof of stake which builds consensus using a similar idea) but using it in real life seems impractical mainly due to social factors:

1. This introduces luck to the markets. Imagine there's a large ticket for value of $1000 that requires $1 to buy. It's open to the market, so anybody can buy as many tickets as they want. Anybody who buys a ticket is EV neutral, however, imagine a person decided to buy lots of tickets that are unlikely to hit and then got "unlucky". They would then lose their money, whereas in the regular scheme, they may pay a transaction cost that the vendor places on them, but they can never be "unlucky", since there's no variance in outcomes
2. Fraudulent elections always have to be checked -- if you can defraud the election process at all, or find a way to withhold information, you can make lots of money.
3. People are unlikely to be able to calculate EV with variance -- I would assume most people would simply lose their money with this scheme, whereas a classic no-variance scheme would not have this issue. This would just increase inequality. I'd say look at option markets, where a vast majority of participants lose money even though technically there should be no information asymmetry -- and outcomes become worse as less experienced participants enter.


