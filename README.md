# Personal Portfolio & WebAssembly Visualizer

A sleek, responsive single-page developer portfolio showcasing ECE, Embedded Systems, and Data Science projects. It features live coding activity grids (GitHub & Codeforces) and an interactive WebAssembly-powered pathfinding visualizer.

---

## 🚀 How to Run the Site Locally

Because this site loads a WebAssembly binary (`dijkstra.wasm`) to compute paths, browsers prevent opening the file directly via `file://` paths due to security/CORS rules. 

You must run a simple local web server to view the site:

### Method A: Using Python (Pre-installed)
1. Open your terminal/PowerShell in this directory.
2. Run:
   ```bash
   python -m http.server 8000
   ```
3. Open your browser and navigate to **[http://localhost:8000](http://localhost:8000)**.

### Method B: Using Node.js (Pre-installed)
1. Open your terminal/PowerShell in this directory.
2. Run:
   ```bash
   npx http-server -p 8000
   ```
3. Open your browser and navigate to **[http://localhost:8000](http://localhost:8000)**.

---

## ✨ Portfolio Key Features

- **Responsive Theme Toggling**: Seamless transition between sleek dark slate and clean light themes (preference persisted in local storage).
- **Coding Activity Grids**: 
  - **GitHub**: Dynamically fetches and styles month labels and cells (rounded, white-themed in dark mode).
  - **Codeforces**: Queries API data live to render profile rankings, problem counts, and a color-coded submission calendar.
- **WASM Dijkstra Pathfinder**: An interactive grid visualizer compiled from C to WebAssembly. 
  - *How to trigger*: Appears as an **Easter Egg** modal via a slide-in invitation toast after **2 minutes** on the page, or by clicking the launcher link in the footer.
  - *Interactions*: Drag flags to change starting/target coordinates, drag-and-paint charcoal walls, and watch the cyan wavefront search and neon yellow shortest path animate at native WASM speed.
- **Web3Forms Integration**: Fully validated, optional-message contact form.

---

## 🌐 Deploying to Production

To deploy online for free, either:
1. **GitHub Pages**: Push this Git repository to GitHub and enable **GitHub Pages** from the repository settings.
2. **Vercel / Netlify**: Drag and drop this folder directly into [Vercel](https://vercel.com/) or [Netlify](https://www.netlify.com/) for instant publishing.
