import { createRouter, createWebHashHistory } from 'vue-router';
import Access from '@/components/Access.vue';
import Home from '@/components/Home.vue';
import Settings from '@/components/Settings.vue';
import Info from '@/components/Info.vue';

const routes = [
  { path: '/', component: Access },
  { path: '/home', component: Home },
  { path: '/settings', component: Settings },
  { path: '/info', component: Info }
];

const router = createRouter({
  // In Electron è FONDAMENTALE usare createWebHashHistory
  history: createWebHashHistory(), 
  routes,
});

export default router;