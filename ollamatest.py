from openai import OpenAI

client = OpenAI(
    base_url = 'http://localhost:11434/v1',
    api_key='ollama', # required, but unused
)

response = client.chat.completions.create(
  model="deepseek-r1:1.5b",
  messages=[
    {"role": "system", "content": "You are a computer science Professor at a prestigious university."},
    {"role": "user", "content": "If I have a C program and I want to call a python function from within the C program, how would I do that?"}
  ]
)
print(response.choices[0].message.content)
