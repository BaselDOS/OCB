# Intro:
This project is in the field of hardware for embedded computer systems, where a hardware encryption is implemented on an advanced MicroBlaze processor from Xilinx, as described in the following block diagram:
![image](https://github.com/BaselDOS/OCB/assets/89356793/3e7d20e5-6fb4-430a-af79-d3323af956e0)

Figure 1: Block Diagram

The accelerator is built using the Verilog language, which allows us to build new components that can perform multiple operations in the same clock cycle. For example, the AddShift component can perform both shifting and addition in a single clock cycle instead of two. Building such components that can perform multiple operations in the same clock cycle significantly reduces the algorithm's runtime. Finally, we will test its correctness through simulations, synthesis, and, of course, verify its functionality on the Xilinx Kintex-7 chip according to the requirements.

# Important Note for Further Development:
Our algorithm utilizes the AES national encryption standard to encrypt/decrypt data using the Rijndael functions, which are a group of symmetric functions that help us scramble the rows/columns of the matrices that represent the word we want to encrypt/decrypt or swap parts of the matrix symmetrically using matrices such as Rijndael's s_box, which is equivalent to subtraction, and Inv_s_box, which is equivalent to the "inverse of subtraction."

By using this group of functions, we ensure that the encryption/decryption is as "secure" as possible.

The Rijndael functions are divided into two groups: "multiplication"of matrices and "substitution" matrices. The multiplication matrices are used to mix the columns of the input matrix, while the substitution matrices are used to replace the bytes of the input matrix.

Our algorithm relies on the AES (Advanced Encryption Standard) national encryption standard to encrypt/decrypt data. It uses Rijndael functions, which are a set of symmetric functions that help us shuffle rows/columns of the matrices that represent the word we want to encrypt/decrypt or replace parts of the matrix symmetrically using matrices like the Rijndael's s_box for subtraction and Inv_s_box for inverse subtraction.

By using this set of functions, we ensure that encryption/decryption is as secure as possible.

The Rijndael functions are divided into two groups: "multiplication" functions and "subtraction" functions:

1. The multiplication functions include mul2, mul3, mul9, mul11, mul13, and mul14. For example, mul2 corresponds to "multiplying by 2" and so on.
2. The "subtraction" function and its inverse include sub and isub.

# Motivation:
Why run an encryption algorithm in the first place? And why is it worth speeding up?
The answers to these questions are simple... security.
Encryption is the best method to protect data, ensuring that only those with the "tools" to perform the appropriate decryption can access it. And in today's world, where time is crucial, it's preferable to use hardware accelerators. Performing encryption that takes weeks, days, or even hours can impact a company's position in the market and make them lose out to competitors.
Using software or hardware alone to perform encryption provides either a "good" but very time-consuming encryption or a fast encryption but with poor security. Hence, the need for an intermediate solution that combines hardware and software approaches.
Another interesting question: has anyone done this before?
Yes, there are several alternatives, such as CBC (Cipher Block Chaining) and EBC (Electronic Codebook) methods. So why OCB?
EBC divides data into separate blocks and uses a shared encryption key for all blocks. This compromises the level of encryption, as even if we encrypt any image, we can still recognize the original form of the image. On the other hand, CBC also divides data into blocks, but each block has a different encryption key. However, the initialization vector (IV) is transmitted along with the encrypted file, which can compromise security.

# Approach to the problem solution
Before starting the work, we need to:
1. Dive deep into the OCB encryption algorithm and the AES encryption standard based on it.
2. Learn how the MicroBlaze processor works and its characteristics.
3. Learn how to build a platform and how to use Vitis software to run and connect the algorithm with the hardware accelerator.
# Work stages
After researching and learning the required materials:
1. Write efficient and well-organized C code.
2. Perform profiling to identify which part(s) should be offloaded to the hardware accelerator.
3. Write Verilog hardware code for the accelerator and verify it using simulations (test benches).
4. Connect the accelerator to the platform and make the necessary modifications to the algorithm.
5. Run the algorithm once without the accelerator and once with it, and analyze the results.
# Project goals:
After obtaining the results and producing all the required reports, we will go over everything, especially the three most significant reports in the VLSI world, which are:
1. Timing report: Ensure that all timing requirements of the system are met, with no setup and hold errors.
2. Power report: Examine the power consumption of the component and ensure that the wasted power is minimal, preferably not exceeding 25% of the power wasted by the processor itself.
3. Utilization report: Focus on minimizing the area occupied by the component, aiming not to exceed 40% of the processor's area.

An additional requirement is to measure the time (in clock cycles) it takes for our component to run and perform everything, and we demand that our execution time be as low as possible. In the worst case, we expect to achieve a 10% improvement in execution time when using an accelerator compared to running without it. All these tests and more will initially be performed using simulations in Xilinx's Vivado software, and then we will verify if all these requirements are met in real-time on the chip using Vitis.
# Project Description:
The OCB encryption algorithm is described by its pseudo code:

![image](https://github.com/BaselDOS/OCB/assets/89356793/d5f7231b-6aae-40ca-8466-dec39b6265a1)

which is equivilent to this block diagram:
![image](https://github.com/BaselDOS/OCB/assets/89356793/a3396ab2-95c9-4107-aa5c-322c1fe073b2)

where :
1. M is the message we want to encrypt or decrypt.
2. N represent the nonce.
3. L,R,Z,X and Y are help arrays.
4. E_k means applying AES-128B encryption or decryption using the key K.
5. C is the cipher text.
6. T is the tag.

The algorithm begins by generating a key set from the main key. In our case, since the block size is 128 bits, we generate 10 keys. Then, a set of arrays is generated, which is used for encryption or decryption of the word. According to the software description, a word is generated as the result of encryption/decryption.

Additionally, a new word called "tag" is generated. It is appended to the output if it is an encryption process, or removed before decryption. Then, another word is generated, and through it, we check whether we have reached the original word. If they are identical, there is no problem. However, if they are different, there was an issue, and the output is incorrect.

In simple terms, our algorithm receives a word that needs to be encrypted or decrypted, a key for encryption/decryption, and a nonce. After performing encryption, a ciphertext word is obtained, which is concatenated with a tag. This tag can be used during decryption to check if the correct word is obtained back or not.

# Implementation:
# Software Description:
The code was initially written in Visual Studio and divided into parts, where each part is described by a corresponding function. Each set of functions that describes a specific chapter in the algorithm is written in a relevant module. The code consists of 4 modules, two header files for declaring external functions and including important libraries, and the main C file.

# Classes:

Rijndael_functions: Contains all the functions of Rijndael used for internal AES encryption.
Encrypt_functions: Contains all the required functions for encryption according to the AES standard.
Decrypt_functions: Contains all the required functions for decryption according to the AES standard.
OCB_functions: Contains all the required functions for encrypting/decrypting a complete word.
# Definition Files:

AES_defines: Contains important library inclusions for encrypting a single block and defines enums that describe Rijndael matrix names and error descriptions.
OCB_defines: Contains important library inclusions for encrypting a complete word and defines enums that describe the operation mode (encryption or decryption) and error descriptions.
# Main File:

Main: Connects everything together and encrypts or decrypts the input.
# Description of the Auxiliary Algorithm AES-128B:
The AES standard is known for its 3 configurations: 128 bits, 192 bits, or 256 bits. We decided to implement the encryption algorithm for 128 bits, so encrypting each block will require 11 rounds, as described in the following diagram:
![image](https://github.com/BaselDOS/OCB/assets/89356793/db813d4a-93a5-4095-9ff3-7780532bcff7)

It is important to note that each block is mapped to a 2-dimensional state matrix M_4x4, which is called the State.

Additionally, each stage of the process, including Add_RoundKey, SubBytes, ShiftRows, and MixColumns, utilizes at least one of the Rijndael functions.


# Description of the OCB Algorithm Implementation:
Our algorithm generates several auxiliary arrays: L_Arrays, Z_Arrays, and L_Inv_Array. After initializing these arrays, we divide the input word into an array of blocks. If the length of the word is not a multiple of 128 bits, we pad it with zeros. Then, we perform XOR operations and encryption according to the AES-128B standard, as described in the previous section. This process generates two additional auxiliary arrays, X_Array and Y_Array, which are used to produce the encrypted/decrypted word and the tag, respectively, in the case of encryption, as described in the project description section.

# Description of the Working System:
To run the algorithm on the Kintex-7 KC705 FPGA chip, we built the following platform:
![image](https://github.com/BaselDOS/OCB/assets/89356793/e000e962-c177-4f0c-be03-b24d3b38d93b)


# Description of Hierarchies:

1. MB_System: Contains the MicroBlaze processor with its internal memory (MicroBlaze local memory) and the MicroBlaze debug module (MDM).
 ![image](https://github.com/BaselDOS/OCB/assets/89356793/85e0a468-f265-4e06-bec6-4ef444d5dc34)

Figure 5: Processor Hierarchy

2. Uart_Inv: Contains the uartlite module, which handles the output in a serial manner, and the interconnect module, which connects the processor to the serial interface.

![image](https://github.com/BaselDOS/OCB/assets/89356793/ed448901-6734-4f79-bc06-7926dbbf4a53)

Figure 6: Uart Hierarchy

3. Mig_Inv: Contains the external memory on the chip, its reset unit, and the interconnect component that connects the processor to the external memory. Additionally, this component generates the clock that runs the processor.
![image](https://github.com/BaselDOS/OCB/assets/89356793/81bff06f-0101-45ec-b65b-35270d628936)

Figure 7: Chip Memory Hierarchy

In addition, we connected a timer that allows us to measure the execution time in clock cycles.
Usage:

1. To use the timer commands, we included the xtmrctr.h library.
2. We defined three variables: start_cycles, end_cycles, and elapsed_cycles, which represent the initial, final, and elapsed clock cycle counts, respectively.
3. We used the asm volatile("mfs %0, rmsr" : "=r" (start_cycles)) command to measure the initial clock cycle count before starting the encryption.
4. After completing the work, we used the asm volatile("mfs %0, rmsr" : "=r" (end_cycles)) command to measure the final clock cycle count.
5. Finally, we calculated the difference between these two values to determine the required number of clock cycles.
# Profiling Execution:
Using Visual Studio, we performed profiling on our code and obtained a report of the number of calls made to each function. We summarized the top 10 functions with the highest call counts in a table. We also examined the translation of the C code to machine language through Visual Studio to determine which function(s) consumed the most clock cycles. After several iterations, we decided to replace the R_boxes function, which includes the Rijndael matrices and the operations for row/column mixing and Rijndael subtraction, including their inverse operations.

# Hardware Description - Accelerator:
According to the note mentioned in the initial summary, we built a function called R_Boxes, which is responsible for performing the Rijndael functions mentioned earlier. According to table (9.1), we can see that this function has the longest runtime. Therefore, we decided to replace it with a suitable hardware implementation.

We designed the appropriate hardware based on the following block diagram:

![image](https://github.com/BaselDOS/OCB/assets/89356793/f5accf26-880e-494a-9878-5ef9a37fff25)


And, of course, we wrote a testbench for it. After verifying that the output indeed matches the output of the Rijndael functions, we integrated it into a new IP and connected it to the platform shown on the next page.

# Working Environment Description with Accelerators:
After adding our new IP, we obtained the following platform:

![image](https://github.com/BaselDOS/OCB/assets/89356793/d63b8ad7-03aa-48bb-9b28-95c8e211f56d)

Figure 8: General Platform including an Accelerator

Next, we switched back to the Vitis software and examined the xparameters file, which contains information for all components in the platform, including their addresses and memory ranges allocated for each IP that requires memory. We modified our code by writing to the memory corresponding to the inputs of the new IP and then reading from the memory corresponding to its output.

# Analysis of Results:
# Comparison between Design Requirements and Real-Time Results:
Results of running the algorithm without an accelerator:
![image](https://github.com/BaselDOS/OCB/assets/89356793/4d0f0617-e57a-4349-a840-db54dbd8bad2)

Results of running the algorithm with an accelerator:

![image](https://github.com/BaselDOS/OCB/assets/89356793/34d055d9-fe64-4245-9f60-74994f211806)

so in avarage we got :

![image](https://github.com/BaselDOS/OCB/assets/89356793/c28d2bae-af89-4c02-90eb-ff6583039fd1)

Comparison between requirements and results:

![image](https://github.com/BaselDOS/OCB/assets/89356793/dc489c80-0a67-4f6e-8326-67325f651c20)

Table 4: Comparison between requirements and results

In other words, we were able to achieve very good results and meet all the requirements without any setup and hold errors.

# Summary and Conclusions:
As we have seen in the previous chapters, we were able to complete the project with much better results than the requirements. This indicates a significant improvement in runtime with the addition of area and power overhead. Therefore, we can conclude that sometimes it is necessary to consider replacing part of the code written in a programming language with hardware code in order to improve its runtime.

# Recommendations for Further Work:
In our project, we demonstrated how performance can be improved by replacing part of the code written in the C programming language with hardware code. However, there are still unanswered questions that can only be addressed through further experimentation, such as:

1. Should code always be integrated with hardware code?
To answer this question, accelerators should be implemented for several algorithms and compared.

2. Should all the code written in the programming language be replaced with hardware code?
To answer this question, an equivalent hardware code for all algorithms should be developed and the results analyzed.

3. Is the OCB algorithm always the best for encryption, or is it only true in certain cases?
To answer this question, existing encryption algorithms should be analyzed, executed, and compared, while considering if there are any new ideas for implementation that have not yet been explored.

# Additional Chapter - Integration of Dynamic Memory:
During the project, it was highly intriguing to explore the potential effects of replacing static memory with dynamic memory. Essentially, we wanted to investigate whether this change could save unnecessary memory usage and optimize the algorithm. We modified the algorithm to utilize dynamic memory for most of its parts and released the memory at the end of usage. We then ran the algorithm again, both without an accelerator and with an accelerator. The results are summarized in Table (9.2), which compares the performance with dynamic memory to that without it.

![image](https://github.com/BaselDOS/OCB/assets/89356793/f768e184-a42d-469e-b0d9-107501643573)

Table 5: Comparison between Results with and without Dynamic Memory Usage

As can be seen from the table, the clock cycle count without the addition of the accelerator did increase due to memory allocation and deallocation instructions. However, after adding the accelerator, we achieved an improvement of nearly 29%, which is almost 4% more than the experiment without dynamic memory usage. Therefore, we can conclude that the use of dynamic memory improved the performance, and if possible, it is advisable to utilize it.

# Project Documentation:
On the project's website, there is a central folder named OCB, containing a text file called Readme.txt, which provides a similar explanation to the one provided here. Within the main folder, there are several subfolders:

1. Pdf: Inside this folder, you can find the project's work plan, midterm presentation, progress report, and additional reference materials in PDF format.
2. Src: This folder contains subfolders for different programming languages:
2.1 C_Code: Contains two subfolders, each containing two versions of the algorithm, one with dynamic allocations and one without.
2.2 RTL: This folder contains the hardware implementation written in Verilog, as well as the test benches.
2.3 Platforms: Contains both platforms, one with an accelerator and one without.
3. Test_vectors: Contains two text files, each containing input data for testing.
4. Images: Contains JPEG images of the platform's output results in the lab, the executed chip, graphs, and more.
5. Reports: Contains all the generated reports.

# Figures List

![image](https://github.com/BaselDOS/OCB/assets/89356793/c377e753-3ecf-466d-8fb7-c1daad564b4e)

Figure 8.1: Description of the number of calls to the 9 significant functions

In this figure, we present the description of the number of calls made to the 9 significant functions in the project. The functions are labeled and represented with corresponding numbers, indicating the frequency of their execution or invocation during the project's runtime. This information provides insights into the usage and importance of these functions within the project's overall execution flow.

![image](https://github.com/BaselDOS/OCB/assets/89356793/3edbd2ce-b551-4d2c-ae72-1894ae7c1288)

Figure 8.2: Runtime as function of Input length with and without accelerator.

![image](https://github.com/BaselDOS/OCB/assets/89356793/d2898374-c965-4159-b631-9df5aa159c07)

Figure 8.3: Comparison - Runtime as a function of input length without using dynamic memory

This figure compares the runtime of the program as a function of the input length without utilizing dynamic memory. It demonstrates how the execution time changes as the input length varies. The graph or chart presented in this figure illustrates the relationship between the input length and the corresponding runtime, providing insights into the program's efficiency and performance without dynamic memory allocation.

![image](https://github.com/BaselDOS/OCB/assets/89356793/804ed088-b5b7-4a25-bc8e-84f0967d5c12)

Figure 8.4: Comparison - Runtime as a function of input length with dynamic memory usage

In this figure, we compare the runtime of the program as a function of the input length, considering the utilization of dynamic memory. It showcases how the execution time varies with different input lengths when dynamic memory allocation is employed. The graph or chart presented in this figure allows for a comparison of the program's performance and efficiency when utilizing dynamic memory allocation.

![image](https://github.com/BaselDOS/OCB/assets/89356793/4416f041-c724-4212-8256-917215574a3c)

Figure 8.5: The chip utilized in the project

This figure showcases the chip or integrated circuit that was utilized in the project. It may include an image or description of the specific chip or microcontroller used for the implementation. This information provides an understanding of the hardware platform on which the project was executed.
# List of Sources

1.	"OCB - An Authenticated-Encryption Scheme - Background - Rogaway". 2023, link: https://web.cs.ucdavis.edu/~rogaway/ocb/ocb-faq.htm#describe-ocb
2.	Projects, C. T. W., and Projects C. T. W. "Rijndael S-box - Wikipedia". 2005, link: https://en.wikipedia.org/wiki/Rijndael_S-box
3.	Projects, C. T. W., and Projects C. T. W. "Rijndael MixColumns - Wikipedia". 2005, link: https://en.wikipedia.org/wiki/Rijndael_MixColumns
4.	Projects, C. T. W., and Projects C. T. W. "Advanced Encryption Standard - Wikipedia". 2001, link:  https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
5.	The AES128 OCB Mode of Operation, By R.Moskovitz, TruSecure,J.Walker, Intel September 2001, link: https://datatracker.ietf.org/doc/html/draft-moskowitz-aes128-ocb-00
6.	Ahegazy. Ahegazy/aes: Advanced Encryption Standard Implementation in Verilog, link: https://github.com/ahegazy/aes/tree/master#readme
7.	AES – the Advanced Encryption Standard Explained, by Nils Kobald, 8 October 2019, link: https://www.youtube.com/watch?v=h6wvqm0aXco&t=445s&ab_channel=CryptographyforEverybody
And the most important one of all of the resources is a post that were written specially for us:
8.	 How Does Memory Allocation For A Microblaze Work, by Glenn Kirilow (Founder of The EE View),April 16 2023, link: https://www.theeeview.com/how-does-memory-allocation-for-a-microblaze-work/
