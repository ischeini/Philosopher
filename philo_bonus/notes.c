/**
 * Paso 1: alocar memoria de [char ** sem_meals_name];
 * Paso 2: alocar memoria de [pid_t *pid_id]; // Si guardas los pids. (optional)
 * Paso 3: alocar memoria de [sem_t **sem_meals];
 * Paso 3: crear semaphores [/death] [/start] [/print] ([/meals_id] * n_philo + monitor) [/pass] [/priority] [/forks] 
 * Paso 4: crear philosophers proccesses (crear death threads)
 * Paso 5: crear  monitor
 * {
 * 	Paso 6: crear hilo death sem_wait(/death) //(How to not double kill)
 * 	Paso 7: crear hilo meals sem_wait(/meals_monitor) // n_philo times kill
 * 	Paso 8: iniciar [/start]
 * }
 * Paso 9: hacer waitpid(0) de todos los procesos;
 * Paso 10: cerrar semaphoros;
 * Paso 11: liberar memoria;
 */