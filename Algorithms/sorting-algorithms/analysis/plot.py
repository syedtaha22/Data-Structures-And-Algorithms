import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
data = pd.read_csv("algorithms/sorting-algorithms/analysis/sorting_performance.csv")

pd.set_option("display.float_format", "{:.6f}".format)
print(data)


# Extract the columns dynamically (excluding "Array Size")
algorithms = data.columns[1:]  # Exclude the "Array Size" column

# Create the plot
plt.figure(figsize=(10, 6))

# Plot each sorting algorithm's time against the array size dynamically
for algo in algorithms:
    plt.plot(
        data["Array Size"],
        data[algo],
        label=algo,  # Use the algorithm name for the label
    )

# Add labels and title
plt.xlabel("Size of Array (n)")
plt.ylabel("Time Taken (seconds)")
plt.title("Sorting Algorithm Performance Comparison")

# Add a legend to differentiate between the algorithms
plt.legend()

# Show grid and improve layout
plt.grid(True)
plt.tight_layout()

# Save the plot as a PNG file
plt.savefig("algorithms/sorting-algorithms/analysis/sorting_algorithm_performance.png")
# Show the plot
plt.show()
