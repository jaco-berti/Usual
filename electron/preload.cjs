const { contextBridge, ipcRenderer, clipboard } = require("electron");

contextBridge.exposeInMainWorld("api", {
  runProgram: (programName, isShell, ...args) => ipcRenderer.send("run-program", programName, isShell, ...args),
  closeProgram: (programName) => ipcRenderer.send("close-program", programName),
  getKey: () => ipcRenderer.invoke("get-key"),
  getHardwareId: () => ipcRenderer.invoke('get-bios-uuid'),
  copyText: (text) => clipboard.writeText(text),
  scheduledShutdown: (seconds) => ipcRenderer.send("scheduled-shutdown", seconds),
  showChildWin : () => ipcRenderer.send('open-child-window'),
  setEnv: (key, value) => ipcRenderer.send("set-env", key, value),
});