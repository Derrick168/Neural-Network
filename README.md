# Neural Network from Scratch in C++

A simple, educational neural network written for students, by a student.

**Solves the XOR problem** - the classic test that proves neural networks work!

![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=cplusplus)
![Standard](https://img.shields.io/badge/Standard-C%2B%2B17-brightgreen?style=flat-square)
![Status](https://img.shields.io/badge/Status-Working%20Demo-success?style=flat-square)

## What This Is

A neural network that actually works - built from scratch without any fancy libraries.

**Inside:**
- ✅ Matrix operations (multiply, add, etc.)
- ✅ Forward pass (making predictions)
- ✅ Backpropagation (learning)
- ✅ Gradient descent (optimization)
- ✅ Multiple activation functions

**Why XOR?** Because it proves that neural networks with hidden layers can learn things that simple linear models cannot!

## Quick Build & Run

### Linux/Mac:
```bash
cd Neural-Network
g++ -std=c++17 -O2 -o nn src/main.cpp src/NeuralNetwork.cpp src/Matrix.cpp
./nn
```

### Windows (MSVC):
```bash
cl /EHsc /Ox src/main.cpp src/NeuralNetwork.cpp src/Matrix.cpp /Fenn.exe
nn.exe
```

### Using Make:
```bash
make run
```

## Expected Output

```
╔════════════════════════════════════════════════════════════╗
║          Neural Network - XOR Problem Demo                 ║
╚════════════════════════════════════════════════════════════╝

Training for 10000 epochs...
  Epoch 2000/10000 - MSE: 0.249156
  Epoch 4000/10000 - MSE: 0.089234
  ...
  Epoch 10000/10000 - MSE: 0.000345

═════════════════════════════════════════════════════════════
RESULTS - Network Predictions on XOR Problem
═════════════════════════════════════════════════════════════

┌────┬────┬──────────┬──────────┬────────────┐
│ In1│ In2│ Expected │Predicted│ Confidence│
├────┼────┼──────────┼──────────┼────────────┤
│ 0  │ 0  │ 0.0000   │ 0.0245   │ 2.4%     │
│ 0  │ 1  │ 1.0000   │ 0.9876   │ 98.8%    │
│ 1  │ 0  │ 1.0000   │ 0.9812   │ 98.1%    │
│ 1  │ 1  │ 0.0000   │ 0.0189   │ 1.9%     │
└────┴────┴──────────┴──────────┴────────────┘

Overall Accuracy: 100%

✓ XOR Problem Successfully Solved!
```

## Files

```
Neural-Network/
├── include/
│   ├── Matrix.hpp           # Matrix class
│   ├── Activation.hpp       # Sigmoid, ReLU, Tanh
│   └── NeuralNetwork.hpp    # Main network class
├── src/
│   ├── main.cpp             # XOR demo
│   ├── NeuralNetwork.cpp    # Network code
│   └── Matrix.cpp           # Matrix code
├── CMakeLists.txt           # CMake config
├── Makefile                 # Build script
├── README.md                # This file
└── LICENSE                  # MIT License
```

## How It Works

### The Network
```
Inputs (2)
    ↓
Hidden Layer (4 neurons)
    ↓
Output (1)
```

### What Happens During Training

**Step 1: Forward Pass**
```
For each layer:
  1. Multiply input by weights
  2. Add bias
  3. Apply activation function
```

**Step 2: Backpropagation**
```
Work backwards from output:
  1. Calculate error at output
  2. Use chain rule to push error backwards
  3. Find out which weights caused the error
```

**Step 3: Update Weights**
```
For each weight:
  new_weight = old_weight - (learning_rate × error)
```

**Step 4: Repeat**
Do steps 1-3 thousands of times until it learns!

## The XOR Problem

XOR = "exclusive or"

**Truth Table:**
```
0 XOR 0 = 0  (both same)
0 XOR 1 = 1  (different)
1 XOR 0 = 1  (different)
1 XOR 1 = 0  (both same)
```

**Why is XOR special?**
- You can't solve XOR with a straight line
- But a neural network with a hidden layer CAN solve it
- This proves multi-layer networks are more powerful

## Understanding The Code

**All files have detailed comments!**

Start here:
1. [src/main.cpp](src/main.cpp) - See what the demo does
2. [include/NeuralNetwork.hpp](include/NeuralNetwork.hpp) - Understand the network
3. [src/NeuralNetwork.cpp](src/NeuralNetwork.cpp) - See how it works
4. [include/Matrix.hpp](include/Matrix.hpp) - Learn the math

Every function explains:
- What it does
- Why we need it
- How it works

## Try It Out

### Modify the Learning Rate
```cpp
NeuralNetwork nn(0.1);  // Slow and steady
NeuralNetwork nn(0.5);  // Default
NeuralNetwork nn(1.0);  // Fast (might fail!)
```

### Change Network Size
```cpp
// Bigger network
nn.addLayer(2, 8, ActivationType::SIGMOID);
nn.addLayer(8, 1, ActivationType::SIGMOID);
```

### Try Different Activations
```cpp
ActivationType::SIGMOID   // Range: 0 to 1
ActivationType::RELU      // Range: 0 to ∞
ActivationType::TANH      // Range: -1 to 1
```

## Key Concepts

### Sigmoid Activation
- Takes any number
- Squashes it to 0-1
- Creates an S-curve
- Good for "probability" outputs

### Backpropagation
- Uses calculus (chain rule)
- Computes how much each weight messed up
- Works backwards from output

### Gradient Descent
- Follow the error gradient downhill
- Like rolling a ball downhill
- Each step reduces error slightly

### Learning Rate
- Controls step size
- Too high: learn too fast, might diverge
- Too low: learn too slowly

## Troubleshooting

| Problem | Try This |
|---------|----------|
| Network not learning | Increase learning rate or epochs |
| Too slow | Decrease network size or learning rate |
| Diverging | Decrease learning rate |
| Still poor accuracy | More hidden neurons or more epochs |

## License

MIT License - use it however you want!

## Resources to Learn More

- **3Blue1Brown**: Neural Networks on YouTube (visual!)
- **Victor Zhou**: Intro to Neural Networks (article)
- **Andrej Karpathy**: Neural Networks Zero to Hero (video course)

## Questions?

Read the comments in the code - they explain everything!

---

**Made by a student, for students. Star it if it helped! ⭐**
