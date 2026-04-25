<script setup>
import { computed } from 'vue';
import { useRoute, useRouter } from 'vue-router';

const route = useRoute();
const isHome = computed(() => route.path === '/home');
const router = useRouter();

function routeTo(path) {
    router.push(path);
}
</script>

<template>
    <div class="navbar">
        <button>{{ isHome ? "Home" : "Settings" }}</button>
    </div>
</template>

<style scoped>
.navbar {
    width: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
    column-gap: 20px;
}

.navbar > button {
    background-color: transparent;
    color: white;
    font-weight: normal;
    border: none;
    font-size: 16px;
}

.selected {
    font-weight: 600;
}
</style>