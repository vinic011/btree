#include "btree.hpp"
#include <iostream>
#include <cassert>

static btree_ptr<char> read();

int main()
{
  auto root = read();

  const auto visitor = [](btree_ptr<char> tree)
  {
    std::cout << tree->value();
  };

  root->bfs(visitor);
  std::cout << '\n';

  root->dfs(node_ordering::pre_order, visitor);
  std::cout << '\n';

  root->dfs(node_ordering::post_order, visitor);
  std::cout << '\n';

  root->dfs(node_ordering::in_order, visitor);
  std::cout << '\n';
}

static btree_ptr<char> read()
{
  char c;
  std::cin >> c;
  if (c == '(')
  {
    std::cin >> c;
    if (c == ')')
    {
      return btree<char>::make();
    }
    else
    {
      auto x = read();
      auto y = read();
      return btree<char>::make(c, x, y);
    }
  }
  else
  {
    assert(c == ')');
    return read();
  }
}
