import os
__author__ = 'Juampisaez'

for i in ('easy', 'medium', 'hard'):
    if not os.path.exists(f'output/{i}'):
        os.makedirs(f'output/{i}')

os.system(f'./filters tests/easy/test_1.png output/easy/test_1_area_5_60.png area 5 60')
os.system(f'./filters tests/easy/test_1.png output/easy/test_1_delta_05.png delta 0.5')
os.system(f'./filters tests/easy/test_2.png output/easy/test_2_area_12_40.png area 12 40')
os.system(f'./filters tests/easy/test_2.png output/easy/test_2_area_50_5.png area 50 5')
os.system(f'./filters tests/easy/test_2.png output/easy/test_2_delta_001.png delta 0.01')
os.system(f'./filters tests/easy/test_3.png output/easy/test_3_area_50_40.png area 50 40')
os.system(f'./filters tests/easy/test_3.png output/easy/test_3_delta_001.png delta 0.01')
os.system(f'./filters tests/easy/test_3.png output/easy/test_3_delta_01.png delta 0.1')
os.system(f'./filters tests/easy/test_4.png output/easy/test_4_area_18_30.png area 18 30')
os.system(f'./filters tests/easy/test_4.png output/easy/test_4_delta_001.png delta 0.01')

os.system(f'./filters tests/medium/mona_lisa.png output/medium/monalisa_area_5_30.png area 5 30')
os.system(f'./filters tests/medium/mona_lisa.png output/medium/monalisa_delta_025.png delta 0.25')
os.system(f'./filters tests/medium/moon.png output/medium/moon_area_20_50.png area 20 50')
os.system(f'./filters tests/medium/moon.png output/medium/moon_delta_001.png delta 0.01')
os.system(f'./filters tests/medium/moon.png output/medium/moon_delta_005.png delta 0.05')

os.system(f'./filters tests/hard/campus.png output/hard/campus_delta_001.png delta 0.01')
os.system(f'./filters tests/hard/campus.png output/hard/campus_delta_003.png delta 0.03')
os.system(f'./filters tests/hard/campus.png output/hard/campus_delta_005.png delta 0.05')
os.system(f'./filters tests/hard/moon.png output/hard/moon_delta_0008.png delta 0.008')
os.system(f'./filters tests/hard/plate.png output/hard/plate_delta_0005.png delta 0.005')
os.system(f'./filters tests/hard/campus.png output/hard/campus_area_200_0.png area 200 0')
os.system(f'./filters tests/hard/moon.png output/hard/moon_area_500_7.png area 500 7')
os.system(f'./filters tests/hard/plate.png output/hard/plate_area_100_60.png area 100 60')
