#include <memory>
#include <string>
#include <vector>

struct Spa3DMesh
{
  Spa3DMesh(const std::string& mesh_file_name)
  {}

  void show()
  {}
};

struct SpaInterface
{
  virtual ~SpaInterface() = default;
  virtual void show() = 0;
};

struct Spa : public SpaInterface
{
  Spa(const std::string& mesh_file_name)
  {
    // the real object is loading something heavy
    mesh_ = std::make_unique<Spa3DMesh>(mesh_file_name);
  }

  void show() override
  {
    mesh_->show();
  }

  std::unique_ptr<Spa3DMesh> mesh_;
};

class SpaProxy : public SpaInterface
{
public:
  SpaProxy(const std::string& mesh_file_name)
  : mesh_file_name_(mesh_file_name),
    mesh_(nullptr)
  {}

  // the client used the proxy via the same interface as it would use the real object
  void show() override
  {
    // lazy initialization type of proxy
    if (!mesh_)
    {
      mesh_ = std::make_unique<Spa3DMesh>(mesh_file_name_);
    }

    mesh_->show();
  }

private:
  std::string mesh_file_name_;
  std::unique_ptr<Spa3DMesh> mesh_;  
};

int main()
{
  /*
    If we use the simple objects, all meshes would be loaded at startup and this would 
    increase the startup time and the initial memory usage.

    This is avoided when using the proxy, since we load the meshes only when we need them.
  */
  std::vector<Spa> spas;
  spas.emplace_back("mesh1.stl");
  spas.emplace_back("mesh2.stl");
  spas.emplace_back("mesh3.stl");

  for (auto& spa : spas) {
      spa.show();
  }

  std::vector<SpaProxy> spa_proxies;
  spa_proxies.emplace_back("mesh1.stl");
  spa_proxies.emplace_back("mesh2.stl");
  spa_proxies.emplace_back("mesh3.stl");

  for (auto& spa_proxy : spa_proxies) {
      // occures at different times...
      spa_proxy.show();
  }

  // we could also just refactor the class by adding a private loadMesh() function thats called at the same place.

  return 0;
}