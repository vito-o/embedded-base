CC:=gcc

t01_create_test: t01_create_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t02_terminate_test: t02_terminate_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t03_pthread_detach_test: t03_pthread_detach_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t04_pthread_cancel_deferred_test: t04_pthread_cancel_deferred_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


t05_pthread_cancel_async_test: t05_pthread_cancel_async_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t06_pthread_cancel_disabled_test: t06_pthread_cancel_disabled_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t07_race_condition_test: t07_race_condition_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t08_race_condition_mutex_test: t08_race_condition_mutex_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t09_rwlock_test_writer_unlock: t09_rwlock_test_writer_unlock.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t10_rwlock_test: t10_rwlock_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t11_rwlock_test_alternate: t11_rwlock_test_alternate.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t12_rwlock_test_hungry: t12_rwlock_test_hungry.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t13_rwlock_test_hungry_solved: t13_rwlock_test_hungry_solved.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t14_condition_var: t14_condition_var.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t15_unnamed_sem_bin_thread_condition: t15_unnamed_sem_bin_thread_condition.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t16_unnamed_sem_bin_thread: t16_unnamed_sem_bin_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t17_unnamed_sem_bin_process_condition: t17_unnamed_sem_bin_process_condition.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t18_unnamed_sem_bin_process: t18_unnamed_sem_bin_process.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t19_unnamed_sem_count_thread: t19_unnamed_sem_count_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t20_unnamed_sem_count_process: t20_unnamed_sem_count_process.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t21_named_sem_bin: t21_named_sem_bin.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t22_named_sem_count: t22_named_sem_count.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t23_named_sem_no_unlink: t23_named_sem_no_unlink.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t24_thread_pool_test: t24_thread_pool_test.c
	-$(CC) -o $@ $^ `pkg-config --cflags --libs glib-2.0`
	-./$@
	-rm ./$@