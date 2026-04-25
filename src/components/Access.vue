<script setup>
import { ref, onMounted } from 'vue';
import { useRouter } from 'vue-router';

const key = ref('');
const buttonImNewBgColor = ref("919191AA");

const router = useRouter();
const sleep = (ms) => new Promise(resolve => setTimeout(resolve, ms));

async function getKey() {
  const file = await window.api.getKey();
  if(file != undefined) {
    key.value = file;
    buttonImNewBgColor.value = "919191AA";
    await sleep(3000); // per far vedere la key
    router.push("/home");
    return true;
  }
  buttonImNewBgColor.value = "3A8BD7AA";
  return false;
}

async function runCreateUser() {
  if(key.value == '') {
    window.api.runProgram("CreateUser.exe");
    await sleep(2000); // dai tempo di creare
    await getKey();
  }
}

onMounted(async () => {
  await getKey();
});

</script>

<template>
  <center>
    <img src="../assets/user_profile.svg" width="230px">
    <div class="action">
      <input type="text" placeholder="Insert your key" v-model="key">
      <button :style="{backgroundColor: '#' + buttonImNewBgColor}" @click="runCreateUser()">Access</button>
    </div>
  </center>
</template>

<style scoped>

center {
  padding: 30px;
}

.action {
  margin-top: 50px;
}
</style>
