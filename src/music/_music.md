<div>

# \_music {#music .title}

</div>

**Contents**⊕

- [Music](#music)

::: {role="main"}

<div>

## Search

::: {#results}
:::

\

</div>

\<style type=\"text/css\" rel=\"stylesheet\"\> img { height: 150px;
width: 150px; } \</style>

# Music {#music}

\<table> \<tr> \<th>Album Name\</th> \<th>Artist\</th>
\<th>Released\</th> \<th>Cover\</th> \</tr> {{# for row in music }} \<tr>
\<td> {{row.Album}} \</td> \<td> {{row.Artist}} \</td> \<td>
{{row.Released}} \</td> \<td> \<img src=\"{{row.Image}}\"
alt=\"{{row.Album}}\"\> \</td> \</tr> {{# endfor }} \</table>
:::
