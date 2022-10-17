<h1 align="center" style="border-bottom: none; margin-bottom: 0;">
    ft_containers: By <a href="https://github.com/Blenderwizard">Jolan "Blenderwizard" Rathelot</a>
</h1>

## What is this ?

ft_containers is a project from the 42 common core. The goal is to reimplement the c++ stl containers `vector`, `map` and `stack`. These implementations must function similarly to the original containers and can not be more than 20 times slower.

The project also ask to reimplement `std::iterator_traits`, `std::reverse_iterator`, `std::enable_if`, `std::is_integral`, `std::equal` and/or `std::lexicographical_compare`, `std::pair` and `std::make_pair`.

### Map
The implementation of the map uses a Red/Black Tree, a type of rebalancing binary search tree.
