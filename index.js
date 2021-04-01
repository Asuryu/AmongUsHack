const { app, BrowserWindow, Tray, Menu, globalShortcut } = require('electron');
const path = require('path');
const iconPath = path.join(__dirname, '/assets/tray_icon.png');
const fs = require('fs')

let mainWindow;

function createWindow() {
	mainWindow = new BrowserWindow({
		title: "Among Us - Hack",
		width: 200,
		height: 250,
		transparent: true,
		frame: false,
		resizable: false,
		fullscreen: false,
		fullscreenable: false,
		webPreferences: {
			nodeIntegration: true
		},
		icon: __dirname + '/assets/logo.png'
	});
	//   storage.setDataPath(__dirname + "/bin/settings.json");

	// and load the index.html of the app.
	mainWindow.loadFile('index.html');
	mainWindow.webContents.audioMuted = true;
    mainWindow.setAlwaysOnTop(true)

	app.dock.setIcon(__dirname + '/assets/logo.png')

	// mainWindow.webContents.openDevTools();

	// Emitted when the window is closed.
	mainWindow.on('closed', function() {
        globalShortcut.unregisterAll()
		app.quit();
	});
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', function() {

    const ret = globalShortcut.register("Esc", () => {
        app.quit()
    })

	createWindow();
	tray = new Tray(iconPath);
	tray.on('double-click', function() {
		mainWindow.show();
	});

	let template = [
		{
			label: 'Toggle Developer Console',
			role: 'toggleDevTools',
			enabled: true,
			click: function() {
				mainWindow.show();
				mainWindow.toggleDevTools();
			}
		},
		{
			role: 'separator',
			enabled: false
		},
		{
			label: 'Quit Application',
			icon: iconPath,
			role: 'quit'
		}
	];
	const ctxMenu = Menu.buildFromTemplate(template);
	tray.setContextMenu(ctxMenu);
});

// Quit when all windows are closed.
app.on('window-all-closed', function() {
	// On macOS it is common for applications and their menu bar
	// to stay active until the user quits explicitly with Cmd + Q
    globalShortcut.unregisterAll()
    if (process.platform !== 'darwin') app.quit();
});

app.on('activate', function() {
	// On macOS it's common to re-create a window in the app when the
	// dock icon is clicked and there are no other windows open.
	if (mainWindow === null) createWindow();
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
