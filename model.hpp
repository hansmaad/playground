#include <memory>

// shared_ptr version of Sean Parents implementation:
// Value Semantics and Concept-based Polymorphism

class Duct {};

class Model
{
public:
    template<typename T>    
    Model(T model) : 
        model(std::make_shared<ModelT<T>>(std::move(model)))
    {}

    double Calculate(const Duct& duct)
    {
        return model->Calculate(duct);
    }

private:
    struct Concept{
        virtual ~Concept() = default;
        virtual double Calculate(const Duct&) = 0;
    };
    template<typename T>
    struct ModelT : Concept {
        ModelT(T impl) : impl(std::move(impl)) {}
        double Calculate(const Duct& d) override {
            return impl.Calculate(d);
        }
        T impl;
    };

    std::shared_ptr<Concept> model;
};
