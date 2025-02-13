from openai import OpenAI

client = OpenAI(
    base_url = 'http://localhost:11434/v1',
    api_key='ollama', # required, but unused
)
def greet(prompt):
    response = client.chat.completions.create(
        model="deepseek-r1:1.5b",
        messages=[
            {"role": "system", "content": "You are a computer science Professor at a prestigious university."},
            {"role": "user", "content": prompt}
        ] 
    )
    return response.choices[0].message.content
