library(tidyverse)
library(dplyr)
superstore <- read.csv("superstore.csv")

superstore %>%
  select(Sub.Category, Quantity) %>%
  group_by(Sub.Category) %>%
  summarise(Quantity = sum(Quantity)) %>%
  ggplot() +
  geom_col(aes(Sub.Category, Quantity, fill = Sub.Category))
