using System.Net.Http.Headers;
using System.Net.Http.Json;
using Newtonsoft.Json;


namespace CSharpRestClient;

class MainClass
	{
		//static HttpClient client = new HttpClient();
		
		//pentru jurnalizarea operatiilor efectuate si a datelor trimise/primite
		
		static HttpClient client = new HttpClient(new LoggingHandler(new HttpClientHandler()));

		private static string URL_Base = "http://localhost:8080/chat/users";

		public static void Main(string[] args)
		{
			//Console.WriteLine("Hello HttpClient Example");
			RunAsync().Wait();
		}


		static async Task RunAsync()
		{
			client.BaseAddress = new Uri(URL_Base);
			client.DefaultRequestHeaders.Accept.Clear();
			client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
			//Get one user
			String username = "ana";
			Console.WriteLine("Get user {0}", username);
			User result1 = await GetUserAsync("users/"+username);
			Console.WriteLine("Am primit {0}", result1);
			
			
			//Create a user
			User  user = new  User{Id="test_2025a",Name = "Test C#", Passwd = "test"};
			Console.WriteLine("Create user {0}", user);
			User result = await CreateUserAsync("", user);
			Console.WriteLine("Am primit {0}", result);
			Console.ReadLine();
		}
		
		static async Task<User> GetUserAsync(string path)
		{
			HttpResponseMessage response = await client.GetAsync(path);
			if (response.IsSuccessStatusCode)
			{
				var responseString = await response.Content.ReadAsStringAsync();
				User user = JsonConvert.DeserializeObject<User>(responseString);
				return user;
			}
			return null;
		}
		static async Task<User> CreateUserAsync(string path, User user)
		{
			User result = null;
			HttpResponseMessage response = await client.PostAsJsonAsync(path, user);
			if (response.IsSuccessStatusCode)
			{
				var responseString = await response.Content.ReadAsStringAsync();
				result = JsonConvert.DeserializeObject<User>(responseString);
			}
			return result;
		}
	}
public class User
	{
		[JsonProperty("passwd")]
		public string Passwd { get; set; }
		
		[JsonProperty("id")]
		public string Id { get; set; }

		[JsonProperty("name")]
		public string Name { get; set; }
		
		public User[] Friends { get; set; } 

		public override string ToString()
		{
			return string.Format("[User: Passwd={0}, Id={1}, Name={2}, Friends={3}]", Passwd, Id, Name, Friends);
		}
	}
	
public class LoggingHandler : DelegatingHandler
    {
        public LoggingHandler(HttpMessageHandler innerHandler)
            : base(innerHandler)
        {
        }
    
        protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
        {
            Console.WriteLine("Request:");
            Console.WriteLine(request.ToString());
            if (request.Content != null)
            {
                Console.WriteLine(await request.Content.ReadAsStringAsync());
            }
            Console.WriteLine();
    
            HttpResponseMessage response = await base.SendAsync(request, cancellationToken);
    
            Console.WriteLine("Response:");
            Console.WriteLine(response.ToString());
            if (response.Content != null)
            {
                Console.WriteLine(await response.Content.ReadAsStringAsync());
            }
            Console.WriteLine();
    
            return response;
        }
        
        
    }
	
	

