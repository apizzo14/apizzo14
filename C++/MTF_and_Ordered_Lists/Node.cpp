
// Templatized class "Node" represents each item of a MTFList
template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;

    Node();

};

template<typename T>
Node<T>::Node() {
    info = T();
    next = nullptr;
}
//END declaration templatized class Node