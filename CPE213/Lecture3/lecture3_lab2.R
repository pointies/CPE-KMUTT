library(tidyverse)
superstore <- read.csv("superstore.csv")

superstore %>%
  select(Order.Date, Sales) %>%
  mutate(Month = factor(substr(Order.Date,3,7))) %>%
  group_by(Month) %>%
  summarise(Sales = sum(Sales)) %>%
  mutate(Year = (substr(Month,1,2))) %>%
  ggplot(aes(Month, Sales, group = 1, color = Year)) +
  geom_line() +
  geom_point(aes(Month))