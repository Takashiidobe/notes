---
title: social-security-benefits
date created: Monday, July 21st 2025, 6:40:54 am
date modified: Monday, July 21st 2025, 7:13:32 am
---

Currently (for people born after 1960), there are around 3 ages you can take your benefits:
62, 67, 70.

62 is the earliest but offers the least benefits, 67 offers the full benefit, and 70 offers the highest monthly payout.

To calculate your benefits, you need to calculate your Average Indexed Monthly Earnings (AIME) which is your wages for your best 35 years of earnings from 22 to 60 and your Primary Insurance Amount (PIA). 

To calculate AIME:
1. Take annual earnings for each year (up to 35 years). If you do not have 35 years of wage earning, fill with 0.
2. Inflation adjust each earning year 

$$\text{indexed earnings}_y = \text{actual earnings}_y \times \frac{\text{National Average Wage Index in year you turn 60}}{\text{National Average Wage Index in year }y}.$$

3. Sum them up and divide by 420.

$$AIME = \frac{\sum_{i=1}^{35} \text{indexed earnings}_i}{420}.$$
To calculate PIA at current rates:

the first $1226 is effective at 90%,
the next $1226-$7391 is effective at 32%,
and the last $7391+ is effective at 15% rates.

$$PIA = 0.90 \times \min(AIME,1226) + 0.32 \times \max\bigl(\min(AIME,7391) - 1226,\,0\bigr) + 0.15 \times \max(AIME - 7391,\,0).$$

If you claim early, at age 62, then you get a 30% monthly penalty:

$$B_{62} = 0.70 \times PIA.$$

If you claim at age 67, you get the usual amount.

$$B_{67} = 1.00 \times PIA.$$

To calculate when delaying your claim from 62 to 67 is beneficial, we can solve for x where .7 * (x - 62) = (x - 67):

$$0.70\,\mathrm{PIA}\times (X - 62) = 1.00\,\mathrm{PIA}\times (X - 67).$$

$$0.70 (X - 62) = X - 67.$$

$$0.70X - 43.4 = X - 67.$$

$$0.30X = 23.6.$$

$$X \approx 78.67.$$

To calculate the "interest rate" we can calculate the amount delaying your monthly payments for 5 years gets you:


$$0.70\,\mathrm{PIA} \times (1 + r)^5 = 1.00\,\mathrm{PIA}.$$



$$(1 + r)^5 = \frac{1.00}{0.70} \approx 1.4286.$$


About 7.4%:

$$r = \bigl(1.4286\bigr)^{\frac{1}{5}} \;-\; 1 \approx 7.4\%.$$
