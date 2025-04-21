#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

using ll = long long;

static unsigned int p_rand = 1;
int myrand(void) {
    p_rand = p_rand * 1103515245 + 12345;
    return ((unsigned int)(p_rand / 65536) % 100);
}

struct Task {
    int id;
    string name;
    ll duration;
    ll arrival_time;
    vector<string> potential_workshops;
    int k;

    string assigned_workshop_name = "";
    ll start_time = -1;
    ll finish_time = -1;
};

struct PendingTaskInfo {
    int task_id;
    ll duration;
    string name;
    ll arrival_order;

    struct CompareSF {
        bool operator()(const PendingTaskInfo& a, const PendingTaskInfo& b) const {
            if (a.duration != b.duration) {
                return a.duration < b.duration;
            }
            if (a.name != b.name) {
               return a.name > b.name;
            }
            return a.task_id < b.task_id;
        }
    };

    struct CompareLF {
         bool operator()(const PendingTaskInfo& a, const PendingTaskInfo& b) const {
            if (a.duration != b.duration) {
                return a.duration > b.duration;
            }
             if (a.name != b.name) {
               return a.name > b.name;
            }
            return a.task_id < b.task_id;
        }
    };
};

struct Workshop {
    string name;
    string type;
    ll available_at = 0;
    int running_task_id = -1;

    queue<int> pending_tf;
    set<PendingTaskInfo, PendingTaskInfo::CompareSF> pending_sf;
    set<PendingTaskInfo, PendingTaskInfo::CompareLF> pending_lf;

    bool is_idle(ll current_time) const {
        return running_task_id == -1;
    }

    bool has_pending() const {
        if (type == "TF") return !pending_tf.empty();
        if (type == "SF") return !pending_sf.empty();
        if (type == "LF") return !pending_lf.empty();
        return false;
    }

    int peek_next_task_id() const {
        if (!has_pending()) return -1;
        if (type == "TF") return pending_tf.front();
        if (type == "SF") return pending_sf.begin()->task_id;
        if (type == "LF") return pending_lf.begin()->task_id;
        return -1;
    }

    void remove_next_task() {
        if (!has_pending()) return;
        if (type == "TF") {
            pending_tf.pop();
        } else if (type == "SF") {
            pending_sf.erase(pending_sf.begin());
        } else if (type == "LF") {
            pending_lf.erase(pending_lf.begin());
        }
    }

    void add_pending_task(int task_id, const Task& task_details) {
        if (type == "TF") {
            pending_tf.push(task_id);
        } else {
            PendingTaskInfo info = {task_id, task_details.duration, task_details.name, (ll)task_id};
            if (type == "SF") {
                pending_sf.insert(info);
            } else if (type == "LF") {
                pending_lf.insert(info);
            }
        }
    }
};

struct Event {
    ll time;
    enum Type { TASK_ARRIVAL, TASK_COMPLETION } type;

    int task_id;
    string workshop_name;

    bool operator>(const Event& other) const {
        if (time != other.time) {
            return time > other.time;
        }
        return type < other.type;
    }
};

vector<Task> all_tasks;
map<string, Workshop> workshops;
priority_queue<Event, vector<Event>, greater<Event>> event_queue;

void check_and_start_task(const string& workshop_name, ll current_time);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        string ws_name, ws_type;
        cin >> ws_name >> ws_type;
        workshops[ws_name] = {ws_name, ws_type};
    }

    all_tasks.resize(m);
    for (int i = 0; i < m; ++i) {
        ll t, d;
        int k;
        string s;
        cin >> t >> s >> d >> k;

        all_tasks[i].id = i;
        all_tasks[i].name = s;
        all_tasks[i].duration = d;
        all_tasks[i].arrival_time = t;
        all_tasks[i].k = k;
        all_tasks[i].potential_workshops.resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> all_tasks[i].potential_workshops[j];
        }

        event_queue.push({t, Event::TASK_ARRIVAL, i, ""});
    }

    ll current_time = 0;
     if (!event_queue.empty()) {
         current_time = event_queue.top().time;
     }


    while (!event_queue.empty()) {
        Event current_event = event_queue.top();
        event_queue.pop();

        current_time = current_event.time;

        if (current_event.type == Event::TASK_ARRIVAL) {
            int task_id = current_event.task_id;
            Task& arriving_task = all_tasks[task_id];

            string assigned_ws_name = "";
            int num_potential = arriving_task.k;
            for (int j = 0; j < num_potential; ++j) {
                string potential_ws_name = arriving_task.potential_workshops[j];
                ll probability_percent = (100 / num_potential);

                if (j == num_potential - 1 || (myrand() < probability_percent)) {
                    assigned_ws_name = potential_ws_name;
                    break;
                }
            }
            arriving_task.assigned_workshop_name = assigned_ws_name;

             Workshop& assigned_workshop = workshops[assigned_ws_name];
             assigned_workshop.add_pending_task(task_id, arriving_task);

            check_and_start_task(assigned_ws_name, current_time);

        } else {
            string ws_name = current_event.workshop_name;
            Workshop& workshop = workshops[ws_name];

             int finished_task_id = workshop.running_task_id;
             if(finished_task_id != -1) {
                 all_tasks[finished_task_id].finish_time = current_time;
             }

            workshop.running_task_id = -1;

            check_and_start_task(ws_name, current_time);
        }
    }

    vector<Task> finished_tasks;
    for(const auto& task : all_tasks) {
        if (task.finish_time != -1) {
            finished_tasks.push_back(task);
        }
    }

    sort(finished_tasks.begin(), finished_tasks.end(), [](const Task& a, const Task& b) {
        if (a.finish_time != b.finish_time) {
            return a.finish_time < b.finish_time;
        }
        return a.id < b.id;
    });

    for (const auto& task : finished_tasks) {
        cout << task.finish_time << " " << task.name << "\n";
    }

    return 0;
}

void check_and_start_task(const string& workshop_name, ll current_time) {
    Workshop& ws = workshops[workshop_name];

    if (ws.is_idle(current_time) && ws.has_pending()) {

        int next_task_id = ws.peek_next_task_id();
        if(next_task_id == -1) return;

        Task& task_to_start = all_tasks[next_task_id];

        ws.remove_next_task();

        ws.running_task_id = next_task_id;
        ws.available_at = current_time + task_to_start.duration;
        task_to_start.start_time = current_time;

        event_queue.push({ws.available_at, Event::TASK_COMPLETION, -1, workshop_name});
    }
}