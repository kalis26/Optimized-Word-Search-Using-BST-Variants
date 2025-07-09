import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# --- Plots for output1.csv ---
csv_path1 = 'output1.csv'
df1 = pd.read_csv(csv_path1)

print("Data Table (output1.csv):")
print(df1)

# --- Plots for output2.csv ---
csv_path2 = 'output2.csv'
df2 = pd.read_csv(csv_path2)

print("Data Table (output2.csv):")
print(df2)

x2 = np.arange(len(df2['Simulation']))  # the label locations
width2 = 0.35  # the width of the bars

# Bar chart for BST0_ALL and BSTS_ALL together (grouped bars, one figure)
plt.figure(figsize=(12, 7))
plt.bar(x2 - width2/2, df2['BST0_ALL'], width2, color='skyblue', label='BST0')
plt.bar(x2 + width2/2, df2['BSTS_ALL'], width2, color='lightgreen', label='BST1/BST2/BST3')
plt.xlabel('Numéro de simulation')
plt.ylabel('Nombre total de noeuds visités')
plt.title('Nombre total de noeuds visités par simulation (Succès et Échec) (BST0 vs BST1, BST2, BST3)')
plt.xticks(x2, df2['Simulation'])
plt.legend(fontsize=16, fancybox=True, edgecolor='black', loc='best')
plt.grid(True, axis='y')

# Annotate BSTS_ALL bars with decimal gain (e.g., 0.12 or -0.07)
percent_gains = []
for i, (bst0, bsts) in enumerate(zip(df2['BST0_ALL'], df2['BSTS_ALL'])):
    if bst0 != 0:
        percent_gain = (bst0 - bsts) / bst0
    else:
        percent_gain = 0
    percent_gains.append(percent_gain)
    plt.text(
        x2[i] + width2/2,
        bsts + max(df2['BST0_ALL'].max(), df2['BSTS_ALL'].max()) * 0.01,
        f"{percent_gain:.2f}",
        ha='center', va='bottom', fontsize=10, color='black'
    )

# Calculate and display average gain (decimal) in French, with bigger font and box
if percent_gains:
    avg_gain = sum(percent_gains) / len(percent_gains)
    plt.text(
        0.99, 0.95,
        f"Gain moyen d'efficacité (%): {avg_gain*100:.2f}",
        ha='right', va='top',
        transform=plt.gca().transAxes,
        fontsize=20,  # Bigger font size
        color='darkgreen',
        bbox=dict(facecolor='white', alpha=0.7, edgecolor='none')
    )

plt.tight_layout()

# --- Plots for output3.csv ---
csv_path3 = 'output3.csv'
if os.path.exists(csv_path3) and os.path.getsize(csv_path3) > 0:
    df3 = pd.read_csv(csv_path3)
    print("Data Table (output3.csv):")
    print(df3)

    x3 = np.arange(len(df3['Simulation']))  # the label locations
    width3 = 0.35  # the width of the bars

    # Bar chart for BST0_Range_Total and BSTS_Range_Total together (grouped bars, one figure)
    plt.figure(figsize=(12, 7))
    plt.bar(x3 - width3/2, df3['BST0'], width3, color='deepskyblue', label='BST0')
    plt.bar(x3 + width3/2, df3['BST1/BST2/BST3'], width3, color='limegreen', label='BST1/BST2/BST3')
    plt.xlabel('Numéro de simulation')
    plt.ylabel('Nombre total de noeuds visités')
    plt.title('Nombre total de noeuds visités par simulation (BST0 vs (BST1, BST2, BST3))')
    plt.xticks(x3, df3['Simulation'])
    plt.legend()
    plt.grid(True, axis='y')
    plt.tight_layout()

    # Annotate BSTS_Range_Total bars with percentage gained
    percent_gains_range = []
    for i, (bst0, bsts) in enumerate(zip(df3['BST0'], df3['BST1/BST2/BST3'])):
        if bst0 != 0:
            percent_gain = (bst0 - bsts) * 100 / bst0
        else:
            percent_gain = 0
        percent_gains_range.append(percent_gain)
        plt.text(
            x3[i] + width3/2,
            bsts + max(df3['BST0'].max(), df3['BST1/BST2/BST3'].max()) * 0.01,
            f"{percent_gain/100:.2f}",  # Decimal format
            ha='center', va='bottom', fontsize=10, color='black'
        )

    # Calculate and display average gain percentage for range searches
    if percent_gains_range:
        avg_gain_range = sum(percent_gains_range) / len(percent_gains_range)
        plt.text(
            0.99, 0.95,
            f"Gain moyen d'efficacité (%): {avg_gain_range:.2f}",
            ha='right', va='top',
            transform=plt.gca().transAxes,
            fontsize=20,  # Bigger font size
            color='darkgreen',
            bbox=dict(facecolor='white', alpha=0.7, edgecolor='none')
        )

    # Make the legend font bigger and the box more visible
    plt.legend(fontsize=16, fancybox=True, edgecolor='black', loc='best')

else:
    print("output3.csv is missing or empty. Skipping plots for output3.csv.")

# Prepare the comparative DataFrame with new column names
comparative_df = pd.DataFrame({
    'Simulation': df1['Simulation'],
    'BST0 Success': df1['BST0_Success'],
    'Trip Success': df1['BSTS_Success'],
    'BST0 Fail': df1['BST0_Fail'],
    'Trip Fail': df1['BSTS_Fail'],
})

def highlight_lesser(row):
    styles = ['']  # For 'Simulation' column
    # Success columns
    if row['BST0 Success'] < row['Trip Success']:
        styles += ['background-color: #ffcccc; font-weight: bold', '']
    elif row['Trip Success'] < row['BST0 Success']:
        styles += ['', 'background-color: #ccffcc; font-weight: bold']
    else:
        styles += ['', '']
    # Fail columns
    if row['BST0 Fail'] < row['Trip Fail']:
        styles += ['background-color: #ffcccc; font-weight: bold', '']
    elif row['Trip Fail'] < row['BST0 Fail']:
        styles += ['', 'background-color: #ccffcc; font-weight: bold']
    else:
        styles += ['', '']
    return styles

# Apply the highlighting
styled_table = comparative_df.style.apply(highlight_lesser, axis=1)

# Add table styles for borders, gridlines, and header formatting
styled_table = (
    styled_table
    .set_table_styles(
        [
            {'selector': 'th', 'props': [('font-size', '16px'), ('font-weight', 'bold'), ('border', '2px solid black'), ('text-align', 'center')]},
            {'selector': 'td', 'props': [('border', '1px solid black'), ('text-align', 'center'), ('font-size', '14px')]},
            {'selector': 'table', 'props': [('border-collapse', 'collapse'), ('margin', '0 auto')]}
        ]
    )
    .set_properties(**{'text-align': 'center'})
    .hide(axis="index")
)

# Save as HTML
styled_table.to_html('comparative_table.html')

plt.show()