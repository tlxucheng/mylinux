/* https://blog.csdn.net/weixin_40066612/article/details/104073693 */

#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char *s)
{
    int size   = 0;
    int num    = 0;
	int i      = 0;
    int j      = 0;
	int k      = 0;

	size = strlen(s);
    for(j = 0; j < size; j++)
	{
		for(k = i; k < j; k++)
		{
            if(s[k] == s[j])
			{
				i = k+1;
				break;
			}
		}

		if(j-i+1 > num)
	    {
            num = j-i+1;
		}
	}

    return num;
}

int main()
{
	char s[] = "abcabcbb";
	printf("%s\n", s);
	printf("%d\n", lengthOfLongestSubstring(s));
	
	return 0;
}
