<script setup>
import { ref } from 'vue';
import Navbar from './Navbar.vue';
import { useRouter } from 'vue-router';

const router = useRouter();
const sleep = (ms) => new Promise(resolve => setTimeout(resolve, ms));
const bgCopyUUID = ref(false);
const isClientKeyOpen = ref(false);
const isClientScreenOpen = ref(false);
const isScheduledShutdown = ref(false);
const isRemoveSaved = ref(false);
const isAllRemoved = ref(false);
const isCloseConnectionOnAltTab = ref(false);
const isCloseConnectionOnKey = ref(false);

async function copyHardwareId() {
    bgCopyUUID.value = true;
    const result = await window.api.getHardwareId();
    if (result) window.api.copyText(result);
    await sleep(500);
    bgCopyUUID.value = false;
}

function routeTo(path) {
    router.push(path);
}

async function openCloseClientKeyboard() {
    if (isClientKeyOpen.value)
        window.api.closeProgram("ClientKeyboard.exe");
    else
        await window.api.runProgram("ClientKeyboard.exe", false);

    isClientKeyOpen.value = !isClientKeyOpen.value;
}

async function openCloseClientScreen() {
    if (isClientScreenOpen.value)
        window.api.closeProgram("ClientScreenShare.exe");
    else
        await window.api.runProgram("ClientScreenShare.exe", false);

    isClientScreenOpen.value = !isClientScreenOpen.value;
}

function removeSaved() {
    if (isRemoveSaved.value)
        window.api.setEnv("REMOVE_SAVED_ON_CLOSE", false);
    else {
        window.api.setEnv("REMOVE_SAVED_ON_CLOSE", true);
        window.api.setEnv("REMOVE_SAVED_ON_CLOSE_ALL", false);
        isAllRemoved.value = false;
    }

    isRemoveSaved.value = !isRemoveSaved.value;
}

function removeAllSaved() {
    if(isAllRemoved.value) {
        window.api.setEnv("REMOVE_SAVED_ON_CLOSE_ALL", false);
    } else {
        window.api.setEnv("REMOVE_SAVED_ON_CLOSE_ALL", true);
        window.api.setEnv("REMOVE_SAVED_ON_CLOSE", false);
        isRemoveSaved.value = false;
    }
    isAllRemoved.value = !isAllRemoved.value;
}

function scheduledShutdown() {
    if (isScheduledShutdown.value)
        window.api.scheduledShutdown(0);
    else
        window.api.scheduledShutdown(60 * 1);
    isScheduledShutdown.value = !isScheduledShutdown.value;
}

function showInfoWin() {
    window.api.showChildWin();
}

async function blockDevide() {
    await window.api.runProgram("Freeze.exe");
}

async function closeConnOnAltTab() {
    if (isCloseConnectionOnAltTab.value)
        window.api.closeProgram("DisableConnectionOnAltTab.exe");
    else
        await window.api.runProgram("DisableConnectionOnAltTab.exe", false);

    isCloseConnectionOnAltTab.value = !isCloseConnectionOnAltTab.value;
}

async function closeConnOnKey(key) {
    if (isCloseConnectionOnKey.value)
        window.api.closeProgram("DisableConnectionOnKey.exe");
    else
        await window.api.runProgram("DisableConnectionOnKey.exe", false, key);

    isCloseConnectionOnKey.value = !isCloseConnectionOnKey.value;
}

</script>

<template>
    <Navbar />
    <div class="options">
        <div class="option">
            <button @click="routeTo('/settings')">Impostazioni</button>
            <button @click="showInfoWin">Informazioni</button>
        </div>
        <div class="option">
            <button @click="openCloseClientKeyboard" :class="{ 'bluebg': isClientKeyOpen }">Registra tastiera</button>
            <button @click="openCloseClientScreen" :class="{ 'bluebg': isClientScreenOpen }">Registra schermo</button>
        </div>
        <div class="option">
            <button @click="removeSaved" :class="{ 'bluebg': isRemoveSaved }">Rimuovi salvataggi alla chiusura</button>
            <button @click="removeAllSaved" :class="{ 'bluebg': isAllRemoved }">Rimuovi tutto alla chiusura</button>
        </div>
        <div class="option">
            <button @click="blockDevide">Blocca dispositivo</button>
            <button @click="scheduledShutdown" :class="{ 'bluebg': isScheduledShutdown }">Spegnimento
                programmato</button>
        </div>
        <div class="option">
            <button @click="closeConnOnKey('ALT')" :class="{ 'bluebg': isCloseConnectionOnKey }">Rimuovi connessione alla premuta del tasto</button>
            <button @click="closeConnOnAltTab" :class="{ 'bluebg': isCloseConnectionOnAltTab }">Rimuovi connessione alla premuta di alt + tab</button>
        </div>
        <div class="option">
            <button>Auto elimina programma</button>
            <button @click="copyHardwareId" :class="{ 'bluebg': bgCopyUUID }">Copia Hardware ID</button>
        </div>
    </div>
</template>

<style scoped>
.options {
    margin-top: 50px;
    display: flex;
    flex-direction: column;
    row-gap: 20px;
}

.option {
    display: flex;
    justify-content: center;
    column-gap: 20px;
}

.option button {
    width: 180px;
    height: 52px;
    font-weight: 500;
    background-color: rgba(240, 240, 240, 0.719);
    border: none;
    border-radius: 4px;
    transition: all 0.5s ease;
}

.bluebg {
    background-color: rgb(58, 139, 215) !important;
    color: white;
}
</style>