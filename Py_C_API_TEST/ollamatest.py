from openai import OpenAI

client = OpenAI(
    base_url = 'http://localhost:11434/v1',
    api_key='ollama', # required, but unused
)
def comment(prompt):
    response = client.chat.completions.create(
        model="llama3.1:8b",
        messages=[
            {"role": "system", "content": "You are a computer programmer that is working on documenting code given to you in a prompt."},
            {"role": "user", "content": prompt}
        ] 
    )
    return response.choices[0].message.content
