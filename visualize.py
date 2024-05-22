import pandas as pd
import os
import matplotlib.pyplot as plt
from pathlib import Path

# Load the data
current_dir = Path(__file__).parent
df = pd.read_csv(current_dir / 'data/eye_tracking_pupil_coordinates.csv')

# Visualize the coordinates over time
plt.figure(figsize=(10, 5))
plt.plot(df['frame_no'], df['x'], label='X Coordinate')
plt.plot(df['frame_no'], df['y'], label='Y Coordinate')
plt.xlabel('Frame')
plt.ylabel('Coordinate')
plt.title('Pupil Centroid Coordinates Over Time')
plt.legend()
plt.savefig(current_dir / 'coordinates.png')

# Visualize the fit quality over time
plt.figure(figsize=(10, 5))
plt.plot(df['frame_no'], df['fit_quality'], label='Fit Quality', color='r')
plt.xlabel('Frame')
plt.ylabel('Fit Quality')
plt.title('Fit Quality Over Time')
plt.legend()
plt.savefig(current_dir / 'fit_quality.png')