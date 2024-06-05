#include<iostream>
#include<string>
using namespace std;

class Post{
protected:
    string username;
    string content;
    bool hasPhoto;
    int numLikes;
public:
    Post(const string &username, const string &content, bool hasPhoto, int numLikes)
    : username(username), content(content), hasPhoto(hasPhoto), numLikes(numLikes) {}

    virtual double popularity()=0;
    virtual void print(){
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        cout<< hasPhoto ? "With photo\n" : "Without photo\n";
        cout<<"Likes "<<numLikes<<" ";
    }

    bool operator>=(Post &p){
        return popularity()>=p.popularity();
    }

    bool operator>(Post &p){
        return popularity()>p.popularity();
    }

    bool isHasPhoto() const {
        return hasPhoto;
    }
};

class FacebookPost : public Post{
private:
    int numShares;
public:
    FacebookPost(const string &username, const string &content, bool hasPhoto, int numLikes, int numShares)
    : Post(username, content, hasPhoto, numLikes), numShares(numShares) {}

    double popularity() override{
        double popularity=numLikes*numShares;
        if(hasPhoto){
            popularity*=1.20;
        }

        return popularity;
    }

    void print() override{
        cout<<"Facebook post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        cout<< hasPhoto ? "With photo\n" : "Without photo\n";
        cout<<"Likes "<<numLikes<<" Shares:"<<numShares<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

class TwitterPost : public Post{
private:
    int numRetweets;
    int numReplies;
public:
    TwitterPost(const string &username, const string &content, bool hasPhoto, int numLikes, int numRetweets, int numReplies)
            : Post(username, content, hasPhoto, numLikes), numRetweets(numRetweets), numReplies(numReplies) {}

    double popularity() override{
        double popularity=numLikes*numReplies*numRetweets;
        if(hasPhoto){
            popularity*=1.10;
        }
        if(content.find("#crypto"));{
            popularity*=1.20;
        }

        return popularity;
    }

    void print() override{
        cout<<"Twitter post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        cout<< hasPhoto ? "With photo\n" : "Without photo\n";
        cout<<"Likes "<<numLikes<<" Retweets:"<<numRetweets<<" Replies:"<<numReplies<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

double mostPopularPostWithPhoto(Post **posts, int n){
    double max=-1;
    for(int i=0; i<n; i++){
        if(posts[i]->isHasPhoto() && posts[i]->popularity()>max){
            max=posts[i]->popularity();
        }
    }

    return max;
}

FacebookPost *fbPostWithMaxShares(Post **posts, int n){
    int index=-1;
    for(int i=0; i<n; i++){
        if(dynamic_cast<FacebookPost*>(posts[i])!= nullptr){
            if(posts[i]>posts[index]){
                index=i;
            }
        }
    }

    return dynamic_cast<FacebookPost*>(posts[index]);
}

Post *readFbPost() {
    string username;
    string content;
    bool photo;
    int likes;
    int shares;
    cin.ignore();
    getline(std::cin, username);
    getline(std::cin, content);
    cin >> photo >> likes >> shares;
    return new FacebookPost(username, content, photo, likes, shares);
}

Post *readTwPost() {
    string username;
    string content;
    bool photo;
    int likes;
    int retweets;
    int replies;
    cin.ignore();
    getline(std::cin, username);
    getline(std::cin, content);
    cin >> photo >> likes >> retweets >> replies;
    return new TwitterPost(username, content, photo, likes, retweets, replies);
}

Post **readMultiplePosts(int *n) {

    cin >> *n;
    Post **posts = new Post *[*n];
    for (int i = 0; i < *n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            posts[i] = readFbPost();
        } else {
            posts[i] = readTwPost();
        }
    }
    return posts;
}

int main() {
    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "Test FacebookPost" << endl;
        Post *post = readFbPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 2) {
        cout << "Test TwitterPost" << endl;
        Post *post = readTwPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 3) {
        cout << "Test operator >=" << endl;
        int n;
        Post **posts = readMultiplePosts(&n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if ((*posts[i]) >= (*posts[j])) {
                        cout << i << " >= " << j << endl;
                    } else {
                        cout << i << " < " << j << endl;
                    }
                }
            }
        }
    } else {
        int n;
        Post **posts = readMultiplePosts(&n);
        for (int i = 0; i < n; i++) {
            posts[i]->print();
            cout << endl;
        }
        cout << "The most popular post with photo has a popularity of: " << mostPopularPostWithPhoto(posts, n) << endl;
        cout << "The facebook post with most shares is ";
        fbPostWithMaxShares(posts,n)->print();
    }

    return 0;
}
