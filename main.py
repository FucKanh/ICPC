import streamlit as st
from streamlit_authenticator import Authenticate, Hasher
from upload_and_search import uploadNsearch

def post_authenticate(auth : Authenticate,username):
    # Source: https://github.com/mkhorasani/Streamlit-Authenticator
    """Function after login"""
    
    auth.logout('Logout','sidebar')
    try:
        if auth.reset_password(username,'Reset password','sidebar'):
            st.success('Password modified successfully')
    except Exception as e:
        st.error(e)

    try:
        if auth.update_user_details(username, 'Update user details','sidebar'):
            st.success('Entries updated successfully')
    except Exception as e:
        st.error(e)
            

def main():

    # auth = Authenticate(
    #         credentials=st.secrets['credentials'],
    #         cookie_name=st.secrets['cookie']['name'],
    #         key=st.secrets['cookie']['key'],
    #         cookie_expiry_days=st.secrets['cookie']['expiry_days'],
    #         preauthorized=st.secrets['preauthorized']
    #     )
    

    # name, authentication_status, username = auth.login('Login', 'main')

    # if st.session_state["authentication_status"] is None:
    #     st.write("Please enter username and password")
    #     try:
    #         username_forgot_pw, email_forgot_password, random_password = auth.forgot_password('Forgot password','sidebar')
    #         if username_forgot_pw:
    #             st.success('New password sent securely. Check your email')
    #         else:
    #             st.error('Username not found')
    #     except Exception as e:
    #         st.error(e)

    #     try:
    #         username_forgot_username, email_forgot_username = auth.forgot_username('Forgot username','sidebar')
    #         if username_forgot_username:
    #             st.success('Username sent securely')

    #         else:
    #             st.error('Email not found')
    #     except Exception as e:
    #         st.error(e)
    
    # elif st.session_state["authentication_status"] is False:
    #     st.error('Incorrect username/password')

    # elif st.session_state["authentication_status"]:
        # post_authenticate(auth,username)

    upload_and_search = uploadNsearch('huy')
    code_search,code_upload = st.tabs(['Search code','Submit code'])

    with code_search:
        upload_and_search.codeSearch()

    with code_upload:
        upload_and_search.uploadCode()
        

if __name__ == '__main__':
    main()