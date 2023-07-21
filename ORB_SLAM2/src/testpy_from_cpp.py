import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('elapsed_time', type=str, help='経過時間')
parser.add_argument('string_arg', type=str, help='cv::matからの値をつなげた文字列')
args = parser.parse_args()
# Firebaseのサービスアカウント情報
try:
    cred = credentials.Certificate('./test-cpp-to-firebase-firebase-adminsdk-ruihs-55eb777c49.json')
    app = firebase_admin.initialize_app(cred)
    db = firestore.client()
except Exception as e:
    print(e)
    print("failed to configure firebase")
    

def send_data_to_firebase():
    args_position_list = args.string_arg.split(",")
    float_position_list = list(map(float, args_position_list[:-1]))
    doc_ref = db.collection("positions").document(args.elapsed_time)
    try:
        doc_ref.set({"elapsed_time": args.elapsed_time, "string_arg":float_position_list})
    except Exception as e:
        print(e)
if __name__=="__main__":
    
    if(args==None):
        pass
    else:
        send_data_to_firebase()
    
    