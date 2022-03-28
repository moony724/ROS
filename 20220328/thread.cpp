#include <pthread.h>
#include <signal.h>

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg);
/*
ù��° �ƱԸ�Ʈ�� thread �� �����尡 ���������� �����Ǿ����� ������ �����带 �ĺ��ϱ� ���ؼ� ���Ǵ� ������ �ĺ����̴�.
�ι�° �ƱԸ�Ʈ�� attr �� ������ Ư���� �����ϱ� ���ؼ� ����ϸ�, �⺻ ������ Ư���� �̿��ϰ��� �Ұ�쿡 NULL �� ����Ѵ�.
3��° �ƱԸ�Ʈ�� start_routine�� �б���Ѽ� ������ ������ �Լ��̸�,
4��° �ƱԸ�Ʈ�� arg�� ������ �Լ��� �����̴�.
*/

int pthread_join(pthread_t th, void** thread_return);
/*
ù��° �ƱԸ�Ʈ th�� ��ٸ�(join)�� ������ �ĺ����̸�
�ι�° �ƱԸ�Ʈ thread_return�� �������� ����(return) ���̴�.
thread_return �� NULL �� �ƴҰ�� �ش� �����ͷ� ������ ���� ���� �޾ƿü� �ִ�.
*/

int pthread_detach(pthread_t th);
/*
detach�� main �����忡�� pthread_create �� �̿��� ������ �����带 �и���Ų��.
�� �Լ��� �ĺ���ȣth�� �����带 detach ��Ű�µ�
detach �Ǿ������ �ش�(detach ��) �����尡 ����ɰ��
pthread_join �� ȣ������ �ʴ��� ��� ��� �ڿ��� ����(free) �ȴ�
*/

void pthread_exit(void* retval);
/*
pthread_exit �� ���� �������� �����带 �����Ű���� �Ҷ� ����Ѵ�
���� pthread_cleanup_push �� ���ǵǾ� �ִٸ�, pthread_exit �� ȣ��ɰ�� cleanup handler �� ȣ��ȴ�
���� �� cleanup handler �� �޸𸮸� �����ϴ� ���� ���� �ϰ� �ȴ�.
*/

void pthread_cleanup_push(void (*routine) (void*), void* arg);
/*
�̰��� cleanup handlers �� �ν����ϱ� ���ؼ� ���ȴ�
pthread_exit(3)�� ȣ��Ǿ �����尡 ����ɶ� pthread_cleanup_push �� ���ؼ� �ν���� �Լ��� ȣ��ȴ�
routine�� �����尡 ����ɶ� ȣ��Ǵ� �Լ��̴�. arg�� �ƱԸ�Ʈ�̴�.
cleanup handlers �� �ַ� �ڿ��� �ǵ����ְų�, mutex ��ݵ��� ������ ���� �뵵�� ���ȴ�.
���� mutex �������� pthread_exit �� ȣ��Ǿ� ������� �ٸ������忡�� ������ block �ɼ� �ֱ� �����̴�.
���� malloc ���� �Ҵ���� �޸�, ���� ���������ڸ� �ݱ� ���ؼ��� ����Ѵ�.
*/

void pthread_cleanup_pop(int execute);
/*
���� execute �� 0 �̶��, pthread_cleanup_push �� ���� �ν���� cleanup handler �� (�����Ű�� �ʰ�)������ ��Ų��.
0 �� �ƴ� ���ڶ�� cleanup handler �� �����Ű�� ���� �ȴ�.
�׸��� pthread_cleanup_push �� pthread_cleanup_pop �� �ݵ�� ���� �Լ����� ���� ������ ������ �ѽ����� ����ؾ� �Ѵ�.
*/

int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutex_attr* attr);
/*
mutex �� �������� �����尡 �����ϴ� ����Ÿ�� ��ȣ�ϱ� ���ؼ� ���Ǵ� �����ν�
��ȣ�ϰ��� �ϴ� ����Ÿ�� �ٷ�� �ڵ念���� ���� �ѹ��� �ϳ��� �����常 ���డ�� �ϵ��� �ϴ� ������� �����Ǵ� ����Ÿ�� ��ȣ�Ѵ�.
�̷��� �ڵ念��(�ϳ��� �����常 ����������)�� critical section �̶�� �ϸ�, mutex ���� API �� �̿��ؼ� �����Ҽ� �ִ�.
pthread_mutex_init �� mutex ��ü�� �ʱ�ȭ ��Ű�� ���ؼ� ����Ѵ�.
ù��° ���ڷ� �־����� mutex ��ü mutex�� �ʱ�ȭ��Ű��, �ι�° ������ attr �� �̿��ؼ� mutex Ư���� �����Ҽ� �ִ�.
�⺻ mutex Ư���� �̿��ϱ� ���Ѵٸ� NULL �� ����ϸ� �ȴ�.
mutex Ư��(����) ���� "fast", "recurisev", "error checking" �� ������ ������, �⺻���� "fast" �� ���ȴ�.
*/

int pthread_mutex_destroy(pthread_mutex_t* mutex);
/*
���ڷ� �־��� ���ؽ� ��ü mutex �� �����ϱ� ���ؼ� ���ȴ�.
mutex �� pthread_mutex_init()�Լ��� �̿��ؼ� ������ ���ؽ� ��ü�̴�.
pthread_mutex_destroy �� �̿��ؼ� ����� mutex �� �����Ϸ��� �� mutex �� �ݵ�� unlock �����̿��� �Ѵ�.
*/

int pthread_mutex_lock(pthread_mutex_t* mutex);
/*
pthread_mutex_lock �� critcal section �� ���� ���ؼ� mutex lock �� ��û�Ѵ�.
���� �̹� �ٸ� �����忡�� mutex lock �� �� ����ϰ� �ִٸ� �ٸ� �����忡�� mutex lock(���ؽ� ���) �� �����Ҷ�����(����Ҽ� ����������) �� �ȴ�.
���� �ٸ� � �����忡���� mutex lock �� ����ϰ� ���� �ʴٸ�, ��� mutex lock �� ������ �ְ� �ǰ� critcal section �� �����ϰ� �ȴ�.
critcal section ������ ��� �۾��� ���ļ� ����ϰ� �ִ� mutex lock �� ���̻� �ʿ� ���ٸ� pthread_mutex_unlock �� ȣ���ؼ� mtuex lock �� �ǵ����ش�.
*/

int pthread_mutex_unlock(pthread_mutex_t* mutex);
/*
critical section ������ ��� �۾��� ��ġ�� mutex lock �� �����ֱ� ���ؼ� ����Ѵ�.
pthread_mutex_unlock �� �̿��ؼ� mutex lock �� �ǵ����ָ� �ٸ� �����忡�� mutex lock �� ������ �ִ� ���°� �ȴ�.
*/

int pthread_cond_init(pthread_cond_t* cond, const pthread_cond_attr* attr);
/*
pthread_cond_init�� ���ߺ��� (condition variable)cond�� �ʱ�ȭ�ϱ� ���ؼ� ����Ѵ�.
attr �� �̿��ؼ� ���Ǻ����� Ư���� �����Ҽ� ������, NULL �� �ٰ�� �⺻Ư������ �ʱ�ȭ�ȴ�.
���Ǻ��� cond�� ��� PTHREAD_COND_INITIALIZER �� �̿��ؼ��� �ʱ�ȭ �Ҽ� �ִ�.
�� ������ ���� 2���� �ʱ�ȭ ����� �����Ѵ�.
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_init(&cond, NULL);
*/

int pthread_cond_signal(pthread_cond_t* cond);
/*
���Ǻ��� cond�� �ñ׳��� ������. �ñ׳��� ������� cond���� ��ٸ���(wait) �����尡 �ִٸ� �����带 ����� �ȴ�(���Ⱑ Ǯ��).
���� ���Ǻ��� cond�� ��ٸ��� �����尡 ���ٸ�, �ƹ��� �ϵ� �Ͼ�� �ʰԵǸ�, �������� �����尡 ��ٸ��� �ִٸ� ���� �ϳ��� �����忡�Ը� ���޵ȴ�.
�̶� � �����忡�� ��ȣ�� ���޵����� �˼� ����.
*/

int pthread_cond_broadcast(pthread_cond_t* cond);
/*
���Ǻ��� cond���� ��ٸ���(wait) ��� �����忡�� ��ȣ�� ������, ����ٴ� ���� �����ϰ�� pthread_cond_signal�� �����ϰ� �۵��Ѵ�.
*/

int pthread_cond_wait(pthread_cond_t cond, pthread_mutex_t* mutex);
/*
���Ǻ��� cond�� ���ؼ� ��ȣ�� ���޵ɶ����� ���ȴ�. ���� ��ȣ�� ���޵��� �ʴ´ٸ� ������ ���ɼ��� �ִ�.
pthread_cond_wait�� ���Ǳ� ���� mutex ����� �ڵ����� �ǵ����ش�.
*/

int pthread_cond_timedwait(pthread_cont_t* cond, pthread_mutex_t* mutex, const struct timespec* abstime);
/*
���Ǻ��� cond�� ���ؼ� ��ȣ�� ���޵ɶ����� ���Ǹ� �ڵ����� mutex�� �����ִ� �������� pthread_cond_wait�� �����ϴ�.
�׷��� �ð�üũ�� �����ؼ� abstime�ð����� ��ȣ�� �������� �ʴ´ٸ� error �� �߻��ϸ鼭 �����Ѵ�.
�̶� ���ϰ��� ETIMEDOUT �̴�. errno �� ���õǴ°� �ƴ�, ���ϰ����� ������ �Ѿ���°Ϳ� �����ؾ� �Ѵ�.
���� pthread_cond_timedwait�Լ��� �ٸ� signal �� ���ؼ� interrupted �ɼ� ������ �̶� EINTR �� �����Ѵ�.
�� �Լ��� ������ interrupted ��Ȳ�� ���� ó���� ���־�� �Ѵ�.
*/

int pthread_cond_destroy(pthread_cond_t* cond);
/*
pthread_cond_init�� ���ؼ� ������ ���Ǻ���cond�� ���� �ڿ��� �����Ѵ�.
destroy �Լ��� ȣ���ϱ� ���� � �����嵵 cond������ �ñ׳��� ��ٸ��� �ʴ°� Ȯ���ؾ� �Ѵ�.
���� cond �ñ׳��� ��ٸ��� �����尡 �����Ѵٸ� �� �Լ��� �����ϰ� EBUSY �� �����Ѵ�.
*/

int pthread_attr_init(pthread_attr_t* attr);
/*
pthread_attr_init�� thread attribute ��ü�� attr�� ����Ʈ ������ �ʱ�ȭ ��Ų��.
�����Ұ�� 0�� �����ְ� �����Ұ�� -1 �� �ǵ����ش�.
*/

int pthread_attr_destroy(pthread_attr_t* attr);
/*
pthread_attr_init�� ���� ������ thread attribute ��ü�� attr�� �����Ѵ�.
���ŵ� attr �� �ٽ� ����ϱ� ���ؼ��� pthread_attr_init�� �̿��ؼ� �ٽ� �ʱ�ȭ ���־�� �Ѵ�.
*/

int pthread_attr_getscope(const pthread_attr_t* attr, int* scope);
/*
�����尡 � ����(scope)���� �ٷ������ �ִ����� ������ ���ؼ� ���ȴ�.
PTHREAD_SCOPE_SYSTEM�� PTHREAD_SCOPE_PROCESS �� 2���� �����߿� �����Ҽ� �ִ�.
SYSTEM ���� ������� user ��� �������� �Ҹ����, PROCESS ������� Ŀ�θ�� �������� �Ҹ����.
�������� ��� ������� �������ε�, �� Ŀ�ο��� �����带 �����층�ϴ� ����� �ƴ� ������ ���̺귯���� ���ؼ� �����带 �����층 �ϴ� ����� ����Ѵ�.
*/

int pthread_attr_setscope(pthread_attr_t* attr, int scope);
/*
�����尡 � ����(scope)���� �۵��ϰ� �Ұ����� �����ϱ� ���ؼ� ����Ѵ�.
�������� ��� Kernel mode �����带 �������� �������� ���� PTHREAD_SCOPE_SYSTEM ���� �����Ҽ� �ִ�.
�ݸ� �ֶ󸮽��� �������� Ŀ�θ���� ������ �����ϴ�.
*/

int pthread_attr_getdetachstate(pthread_attr_t* attr, int detachstate);
/*
�����尡 join ������ ����(PTHREAD_CREATE_JOINABLE) ���� detached �������� (PTHREAD_CREATE_DETACHED) ������ �˾Ƴ���.
�˾Ƴ� ���� �ƱԸ�Ʈ detachstate�� ����ȴ�.
�⺻�� PTHREAD_CREATE_JOINABLE �̸�, pthread_detach�� �̿��ؼ� ������ �����带 detach ���·� ����������
�Ǵ� pthread_attr_setdetachstate�Լ��� �̿��ؼ� �����带 detache ���·� ������������ PTHREAD_CREATE_DETACHED ���°� �ȴ�.
*/

int  pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate);
/*
�������� ���¸� PTHREAD_CREATE_JOINABLE Ȥ�� PTHREAD_CREATE_DETACHED ���·� �����Ű�� ���ؼ� ���ȴ�.
*/

int pthread_sigmask(int how, const sigset_t* newmask, sigset_t* oldmask);
/*
�����忡�� �ñ׳��� ���� �����ȴ�. �׷������� ���� ���μ����� �ñ׳��� ���޵Ǹ� ���μ����� ������ ��� ������� �ñ׳��� ���޵ȴ�.
�׷��� Ư�� �����常 �ñ׳��� �޵��� �ϰ� ���� ���� ���� ���̴�. �̰�� �� �Լ��� �̿��ϸ� �ȴ�.
*/

int pthread_kill(pthread_t thread, int signo);
/*
������ �ĺ���ȣ thread�� signo��ȣ�� �ñ׳��� �����Ѵ�.
*/

int sigwait(const sigset_t* set, int* sig);
/*
�ñ׳� ������ ���������� ��ٸ���.
*/


//������ ���

int pthread_cancel(pthread_t thread);

int pthread_setcancelstate(int state, int* oldstate);

int pthread_setcancelstate(int state, int* oldstate);

int pthread_setcanceltype(int type, int* oldtype);

void pthread_testcancel(void);