(defn pack_consecutive_duplicates
  "packs consecutive duplicates into a list with lists"
  [lst]
  (group-by identity lst))
