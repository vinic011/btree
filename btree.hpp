#include <memory>
#include <queue>

template <typename T>
class btree;
template <typename T>
using btree_ptr = std::shared_ptr<btree<T>>;
template <typename T>
using queue = std::queue<btree_ptr<T>>;

enum class node_ordering
{
  in_order,
  pre_order,
  post_order,
};

template <typename T>
class btree : public std::enable_shared_from_this<btree<T>>
{
public:
  static btree_ptr<T> make() { return nullptr; }

  static btree_ptr<T> make(T value, btree_ptr<T> lchild = nullptr, btree_ptr<T> rchild = nullptr)
  {
    return btree_ptr<T>(new btree(std::move(value), std::move(lchild), std::move(rchild)));
  }

  T &value() { return value_; }
  const T &value() const { return value_; }


  template <typename Visitor> void bfs(const Visitor &visit)
  {
    queue<T> q;
    q.push(this->shared_from_this());
    while (!q.empty())
    {
      if (q.front()->lchild_)
        q.push(q.front()->lchild_);
      if (q.front()->rchild_)
        q.push(q.front()->rchild_);
      visit(q.front());
      q.pop();
    }
  }

  template <typename Visitor>
  void dfs(node_ordering order, const Visitor &visit)
  {
    switch (order)
    {
    case node_ordering::in_order:
      if (lchild_)
        lchild_->dfs(order, visit);
      visit(this->shared_from_this());
      if (rchild_)
        rchild_->dfs(order, visit);
      return;
    case node_ordering::pre_order:
      visit(this->shared_from_this());
      if (lchild_)
        lchild_->dfs(order, visit);
      if (rchild_)
        rchild_->dfs(order, visit);
      return;
    case node_ordering::post_order:
      if (lchild_)
        lchild_->dfs(order, visit);
      if (rchild_)
        rchild_->dfs(order, visit);
      visit(this->shared_from_this());
      return;
    }
  }

protected:
  btree() = default;

  btree(T value, btree_ptr<T> lchild, btree_ptr<T> rchild) : value_(std::move(value)),
                                                             lchild_(std::move(lchild)),
                                                             rchild_(std::move(rchild))
  {}

private:
  T value_;
  btree_ptr<T> lchild_, rchild_;
};
