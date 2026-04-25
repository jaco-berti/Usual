const { app, BrowserWindow, ipcMain } = require("electron");
const path = require("path");
const { spawn, exec } = require('child_process');
const fs = require('fs');

process.env["REMOVE_SAVED_ON_CLOSE"] = false;
process.env["REMOVE_SAVED_ON_CLOSE_ALL"] = false;
process.env["PROGRAMS_FOLDER"] = "./backend";

let win;
let timerAccessKey = null;
const winURL = () => {
  if (!app.isPackaged) return 'http://localhost:5173';
  else return `file://${path.join(__dirname, '../dist/index.html')}`;
};

app.whenReady().then(() => {
  win = new BrowserWindow({
    title: "Usual",
    width: 500,
    height: 600,
    resizable: false,
    backgroundMaterial: "acrylic",
    vibrancy: "fullscreen-ui",
    autoHideMenuBar: true,
    webPreferences: {
      preload: path.join(__dirname, "preload.cjs"),
      contextIsolation: true,
      sandbox: false
    }
  });

  if (app.isPackaged) {
    addAppToPath();
  }

  // DEV (Vite)
  win.loadURL(winURL());

  // BUILD (commenta sopra e usa questo dopo build)
  // win.loadFile(path.join(__dirname, "../dist/index.html"));
});

app.on('will-quit', async () => {
  if(process.env["REMOVE_SAVED_ON_CLOSE"] === "true")
    await runProgram("RemoveSaved.exe", false);
  if(process.env["REMOVE_SAVED_ON_CLOSE_ALL"] === "true")
    await runProgram("RemoveSaved.exe", false, ["--all"]);
});

async function runProgram(programPath, isShell, ...args) {
  if (isShell) {
    // Per CMD con 'start', gli argomenti vanno messi dentro la stringa del comando
    // Esempio: start "" "C:/path/program.exe" --all
    const shellArgs = ['/c', 'start', '""', programPath, ...args];
    const child = spawn('cmd.exe', shellArgs, {
      detached: true,
      stdio: 'ignore',
      cwd: process.env["PROGRAMS_FOLDER"]
    });
    child.unref();
  } else {
    const child = spawn(programPath, args, { 
      detached: true,
      stdio: 'ignore',
      cwd: process.env["PROGRAMS_FOLDER"]
    });
    child.unref();
  }
}

ipcMain.handle("get-key", async () => {
  try {
    const directoryPath = "C:/Usual/key";

    // Controlliamo se la cartella esiste e ha file
    if (fs.existsSync(directoryPath)) {
      const files = fs.readdirSync(directoryPath);

      if (files.length > 0) {
        clearInterval(timerAccessKey);
        return files[0];
      }
    } else {
      return undefined
    }
  } catch (error) {
    console.error(error);
  }
});

ipcMain.on("run-program", async (event, programName, isShell, ...args) => {
  console.log(args);
  await runProgram(programName, isShell, args);
});

ipcMain.on("close-program", (event, programName) => {
  exec(`taskkill /F /IM ${programName} /T`, (err, stdout, stderr) => {
    if (err) {
      console.error(`Errore nel terminare il processo: ${err.message}`);
      return;
    }
    console.log(`Processo ${programName} terminato con successo.`);
  });
});

ipcMain.handle("get-bios-uuid", async () => {
  return new Promise((resolve, reject) => {
    const getHardwareId = spawn("./backend/HardwareId.exe");
    let result = "";
    getHardwareId.stdout.on('data', (data) => {
      result = data.toString()
    });
    getHardwareId.on('close', (code) => {
      resolve(result);
    });
  })
});

ipcMain.on("scheduled-shutdown", (event, seconds) => {
  exec(`shutdown -a`);

  if (seconds > 0) {
    exec(`shutdown -s -t ${seconds}`);
  }
});

ipcMain.on('open-child-window', (event) => {
  // Recuperiamo la finestra principale per impostarla come "padre"
  const mainWindow = BrowserWindow.fromWebContents(event.sender);

  const childWindow = new BrowserWindow({
    width: 400,
    height: 300,
    parent: mainWindow,      // Imposta il padre
    resizable: false,
    minimizable: false,
    backgroundMaterial: "acrylic",
    vibrancy: "fullscreen-ui",
    autoHideMenuBar: true,
    webPreferences: {
      preload: path.join(__dirname, "preload.cjs"),
      contextIsolation: true,
      sandbox: false
    }
  });

  childWindow.loadURL(`${winURL()}/#/info`);

  childWindow.once('ready-to-show', () => {
    childWindow.show();
  });
});

function addAppToPath() {
  const appFolder = path.dirname(app.getPath('exe'));

  // 2. Comando PowerShell per aggiungere al PATH solo se non è già presente
  const psCommand = `
    $p = "${appFolder}";
    $oldPath = [Environment]::GetEnvironmentVariable('Path', 'User');
    if (-not $oldPath.Split(';').Contains($p)) {
      [Environment]::SetEnvironmentVariable('Path', "$oldPath;$p", 'User');
    }
  `;

  // 3. Eseguilo
  exec(`powershell -Command "${psCommand.replace(/\n/g, ' ')}"`, (err) => {
    if (err) {
      console.error("Impossibile aggiornare il PATH:", err);
    } else {
      console.log("App aggiunta al PATH correttamente!");
    }
  });
}

ipcMain.on("set-env", (event, key, value) => {
  process.env[key] = value;
})