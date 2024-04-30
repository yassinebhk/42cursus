import graphviz

# /bin/python3 /home/yassine/Documents/Github/Push_swap/state_diagram.py
# /usr/local/bin/python3 state_diagram.py

class Node:
    def __init__(self, value):
        self.value = value
        self.before = None
        self.next = None

def create_list(values):
    if len(values) == 0:
        return None

    head = Node(values[0])
    tail = head

    for value in values[1:]:
        new_node = Node(value)
        new_node.before = tail
        new_node.next = head
        tail.next = new_node
        tail = new_node

    head.before = tail
    return head

def insert_node(head, value):
    new_node = Node(value)

    if head is None:
        head = new_node
        new_node.before = new_node
        new_node.next = new_node
    else:
        new_node.before = head.before
        new_node.next = head
        head.before.next = new_node
        head.before = new_node

    return new_node

def traverse_list(head):
    if head is None:
        print("Lista vacía")
        return

    current = head
    while current:
        print(current.value)
        current = current.next

    print()

def generate_graphviz_code(head):
    dot = graphviz.Digraph(name='list_state_diagram')
    dot.attr(rankdir='LR')

    node_attr = {'shape': 'box'}
    dot.node_attr.update(node_attr)

    current_node = head
    previous_node_name = None

    while True:
        node_name = f'node_{current_node.value}'
        dot.node(node_name, label=f'{current_node.value}')

        if previous_node_name:
            dot.edge(previous_node_name, node_name, label='next')
            dot.edge(node_name, previous_node_name, label='before')

        if current_node.next is head:
            dot.edge(node_name, f'node_{head.value}', label='next')
            dot.edge(f'node_{head.value}', node_name, label='before')
            break

        previous_node_name = node_name
        current_node = current_node.next

    return dot

def main():
    # Get the list of integers from the user
    values = []
    while True:
        try:
            value = int(input("Ingrese un valor para el nodo (o 0 para finalizar): "))
            if value == 0:
                break
            values.append(value)
        except ValueError:
            print("Entrada inválida. Ingrese un número entero.")
            continue

    # Create the linked list
    head = create_list(values)

    # Generate the Graphviz code
    graphviz_code = generate_graphviz_code(head)

    # Save the Graphviz code to a file
    with open('list_state_diagram.dot', 'w') as f:
        f.write(graphviz_code.source)

    # Generate the image using Graphviz
    print("Generando imagen del diagrama de estado...")
    graphviz_code.render('list_state_diagram', format='png')
    print("Imagen generada correctamente: list_state_diagram.png")

if __name__ == "__main__":
    main()