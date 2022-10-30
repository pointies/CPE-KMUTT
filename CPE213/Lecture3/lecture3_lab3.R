library(tidyverse)
library(dplyr)
superstore <- read.csv("superstore.csv")

superstore %>%
  select(Region, Discount, Profit) %>%
  ggplot() + 
  geom_jitter(aes(Discount, Profit, color = Region))