import os
import streamlit as st
from supabase import create_client
from streamlit_ace import st_ace

class codeUpload:
    '''Upload code to database and save source code'''
    
    default_ojs = ['Atcoder', 'CSES', 'Codeforce', 'GeeksforGeeks', 'Leetcode', 'USACO', 'VNOJ','Other']
    default_type = ['Binary search', 'DP', 'Data structure', 'Game theory', 'Geometry', 'Graph', 'Greedy', 'Math', 'Matrix', 'String', 'Tree']

    def __init__(self,user) -> None:
        self.current_user = user
        url = 'https://zwiuiboxrduhnkawwnxg.supabase.co'
        key = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Inp3aXVpYm94cmR1aG5rYXd3bnhnIiwicm9sZSI6ImFub24iLCJpYXQiOjE2ODUwMjUyODMsImV4cCI6MjAwMDYwMTI4M30.g8iSc7_F0PirUd3GcxYYlEZ-60sONXRiYg_L58mD3Ro'
        self.spb = create_client(url,key)
        self.spb.auth.sign_in_with_password({"email":"trangiahuy211207@gmail.com","password":"huy21121234"})
        session = self.spb.auth.get_session()
        self.spb.postgrest.auth(session.access_token)
        self.spb.storage.from_("source_code")

        
    def checkInput(self,oj,prob_type,name,id,link) -> None:
        return oj != '' and prob_type != '' and (name != '' or id != '') and link != ''

    def uploadCode(self) -> None:

        with st.form('Submit code'):
            if "submit" not in st.session_state:
                st.session_state['submit'] = False
            oj = st.selectbox(label='OJ', options=self.default_ojs)
            problem_type = st.selectbox(label='Type', options=self.default_type)
            name = st.text_input(label='Name')
            id = st.text_input(label='ID (depend on OJ)')
            link = st.text_input(label='Link to problem')
            code_content = st_ace(theme="dracula",language="c_cpp")

            if st.form_submit_button("Submit code"):
                if (not self.checkInput(oj,problem_type,name,id,link)): st.error('Not valid. Please fill all (name or id is nullable)')
                else:
                    st.session_state['submit'] = True

        file_name = "_".join([oj,problem_type,name,id]) + ".txt"
        executed = False
        if (st.session_state['submit']):
            tmp = self.spb.table("Problem list").select("oj","type","name","oj_id","solved_by").eq("oj",oj).eq("type",problem_type).eq("problem_link",link)
            if (name != ''): tmp = tmp.eq("name",name)
            if (id != ''): tmp = tmp.eq("oj_id",id)

            res = tmp.execute().data
            with open(file_name,"w") as f:
                f.write(code_content)
            
            if res != []:
                st.warning("Problem already existed. Overwrite?")
                st.write(res)
                if st.button("Continue"):
                    executed = True
                    with open(file_name,'rb+') as f:
                        self.spb.storage.from_("source_code").remove([f"source_code/{file_name}"])
                        self.spb.storage.from_("source_code").upload(f"source_code/{file_name}",file_name,{"content-type":"text/plain"})
            else:
                executed = True
                with open(file_name,'rb+') as f:
                        self.spb.storage.from_("source_code").upload(f"source_code/{file_name}",file_name,{"content-type":"text/plain"})

            self.spb.table("Problem list").upsert({"oj":oj,
                                                    "type":problem_type,
                                                    "name":name,
                                                    "oj_id":id,
                                                    "problem_link":link,
                                                    "file_name":file_name,
                                                    "solved_by":self.current_user
                                                }).execute()
            
        
        if os.path.exists(file_name):
            os.remove(file_name)

        if st.session_state['submit'] and executed:
            st.session_state['submit'] = False
            st.experimental_rerun()



def test():
    tmp = codeUpload("huy")
    tmp.uploadCode()

if __name__ == "__main__":
    test()

                

                    

                    



        