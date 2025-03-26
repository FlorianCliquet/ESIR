import random


VECTOR_SIZE = int(input("Entrer la taille du vecteur: "))

with open("build/input.txt", "w") as f:
    f.write(f"{VECTOR_SIZE}\n")
    f.write(" ".join(str(random.uniform(-1000, 1000)) for _ in range(VECTOR_SIZE)) + "\n")
    
    modify_index = random.randint(0, VECTOR_SIZE - 1)
    new_value = random.uniform(-1000, 1000)
    f.write(f"{modify_index}\n{new_value}\n")
    
    f.write(f"{VECTOR_SIZE}\n")
    f.write(" ".join(str(random.uniform(-1000, 1000)) for _ in range(VECTOR_SIZE)) + "\n")
